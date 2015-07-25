#include "tcp_server.h"


using namespace net;

tcp_server::tcp_server(const std::string& address, const std::string& port,
	std::size_t io_service_pool_size)
	: io_service_pool_(io_service_pool_size),
	signals_(io_service_pool_.get_io_service()),
	acceptor_(io_service_pool_.get_io_service()),
	new_connection_(),
	next_conn_id_(0),
	io_master_(acceptor_.get_io_service()),
	strand_(io_master_),
	message_callback_(default_message_callback),
	connection_callback_(default_connection_callback)
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

	SLOG_DEBUG << "server open with ip: " << endpoint.address().to_string() <<
		" port: " << endpoint.port() << " threads: " << io_service_pool_size ;
}

void tcp_server::run()
{
	start_accept();
	//io_work_.run();
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
	new_connection_->set_close_callback(boost::bind(&tcp_server::remove_connection, this, _1));	//this should be "new_connection_"?
}

void tcp_server::handle_accept(const boost::system::error_code& e)
{
	if (!e)
	{
		next_conn_id_++;
		new_connection_->connect_established();

		//remote_endpoint() thread unsafe? cause crash !
		//tcp::endpoint ep = new_connection_->socket().remote_endpoint();

		SLOG_DEBUG << /*ep.address().to_string() << ":" << ep.port() <<*/ "connected. conn id = " << next_conn_id_ ;
	}

	start_accept();
}

void tcp_server::remove_connection(const tcp_connection_ptr& conn){
	conn->io_service().post(boost::bind(&tcp_connection::connect_destroyed, conn));
	io_master_.post(
		/*strand_.wrap*/(boost::bind(&tcp_server::handle_remove_connection, this, conn))
		);
}

void tcp_server::handle_remove_connection(const tcp_connection_ptr& conn){
	SLOG_DEBUG << "master ios : handle_remove_connection " ;
	
}


void tcp_server::handle_stop()
{
	io_service_pool_.stop();
}