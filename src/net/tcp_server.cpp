#include "tcp_server.h"


using namespace net;

tcp_server::tcp_server(const std::string& address, const std::string& port,
	std::size_t io_service_pool_size)
	: io_service_pool_(io_service_pool_size),
	signals_(io_service_pool_.get_io_service()),
	acceptor_(io_service_pool_.get_io_service()),
	new_connection_(),
	n_conn_(0)
{
	// Register to handle the signals that indicate when the server should exit.
	// It is safe to register for the same signal multiple times in a program,
	// provided all registration for the specified signal is made through Asio.
	signals_.add(SIGINT);
	signals_.add(SIGTERM);
#if defined(SIGQUIT)
	signals_.add(SIGQUIT);
#endif // defined(SIGQUIT)
	signals_.async_wait(boost::bind(&tcp_server::handle_stop, this));

	// Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
	boost::asio::ip::tcp::resolver resolver(acceptor_.get_io_service());
	boost::asio::ip::tcp::resolver::query query(address, port);
	boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
	acceptor_.open(endpoint.protocol());
	acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	acceptor_.bind(endpoint);
	acceptor_.listen();

	std::cout << "server open with ip: " << endpoint.address().to_string() << 
		" port: " << endpoint.port() << " threads: " << io_service_pool_size 
		<< std::endl;
}

void tcp_server::run()
{
	start_accept();
	io_service_pool_.run();
}

void tcp_server::start_accept()
{
	new_connection_.reset(new tcp_connection(
		io_service_pool_.get_io_service()));
	acceptor_.async_accept(new_connection_->socket(),
		boost::bind(&tcp_server::handle_accept, this,
		boost::asio::placeholders::error));

	new_connection_->set_connection_callback(connection_callback_);
	new_connection_->set_message_callback(message_callback_);
	new_connection_->set_write_complete_callback(write_complete_callback_);
}

void tcp_server::handle_accept(const boost::system::error_code& e)
{
	if (!e)
	{
		n_conn_++;
		new_connection_->start();

		tcp::endpoint ep = new_connection_->socket().remote_endpoint();
		std::cout << ep.address().to_string() << ":" << ep.port() << "connected. n_conn = " << n_conn_ << std::endl;
	}

	start_accept();
}

void tcp_server::handle_stop()
{
	io_service_pool_.stop();
}