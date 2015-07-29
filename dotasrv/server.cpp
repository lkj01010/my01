
#include "example/echo_server.hpp"
using boost::asio::ip::tcp;

using namespace net;

int main_(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: http_server <threads>\n";
			std::cerr << "  For IPv4, try:\n";
			std::cerr << "    receiver 0.0.0.0 80 1 .\n";
			std::cerr << "  For IPv6, try:\n";
			std::cerr << "    receiver 0::0 80 1 .\n";
			return 1;
		}
#if defined _WIN32
        SLog::InitLog("./logs/dotalog");
#elif   defined _MAC
        SLog::InitLog("/Users/Midstream/Documents/Dev/git-me/my01/dotalog");
#else   //linux
        SLog::InitLog("./logs/dotalog");
#endif

		SLog::SetLevel(slog_debug);

		std::size_t num_threads = boost::lexical_cast<std::size_t>(argv[1]);
//		echo_server s("::1", "12303", num_threads);         //ipv6  localhost
		echo_server s("0.0.0.0", "12303", num_threads);   //ipv4  localhost
		s.run();
	}
	catch (std::exception& e)
	{
		SLOG_EMERGENCY << "exception: " << e.what();
		system("pause");
	}

	return 0;
}
