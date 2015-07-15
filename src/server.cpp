
#include "echo_server.hpp"
using boost::asio::ip::tcp;

using namespace net;

int main(int argc, char* argv[])
{
	try
	{
		/*if (argc != 5)
		{
			std::cerr << "Usage: http_server <address> <port> <threads> <doc_root>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 1 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 1 .\n";
			return 1;
		}*/

		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[1]);
		echo_server s("localhost", "12303", num_threads);

		s.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "exception: " << e.what() << "\n";
		system("pause");
	}

	return 0;
}
