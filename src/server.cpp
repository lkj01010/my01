
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
#ifdef _WIN32
        SLog::InitLog("./sssss");
#else
        SLog::InitLog("/Users/Midstream/Documents/Dev/git-me/my01/sssss");
#endif

		SLog::SetLevel(slog_debug);

		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[1]);
//		echo_server s("::1", "12303", num_threads);         //ipv6  localhost
		echo_server s("127.0.0.1", "12303", num_threads);   //ipv4  localhost
		s.run();
	}
	catch (std::exception& e)
	{
		SLOG_EMERGENCY << "exception: " << e.what();
		system("pause");
	}

	return 0;
}
