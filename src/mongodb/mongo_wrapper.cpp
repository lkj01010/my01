#ifdef _MONGO

#include "mongo_wrapper.h"

using namespace my;
using namespace mongo;
using namespace std;

mongo_wrapper::mongo_wrapper()
{
}

mongo_wrapper::~mongo_wrapper()
{
}

DBClientBase* mongo_wrapper::connect(const string& url){
	if (!instance_.initialized()) {
		std::cout << "failed to initialize the client driver: " << instance_.status() << std::endl;
		throw std::logic_error("failed to initialize mongo");
	}

	std::string errmsg;
	ConnectionString cs = ConnectionString::parse(url, errmsg);

	if (!cs.isValid()) {
		std::cout << "Error parsing connection string " << url << ": " << errmsg << std::endl;
		return NULL;
	}
	DBClientBase* conn = cs.connect(errmsg);
	if (!conn) {
		cout << "couldn't connect : " << errmsg << endl;
		return NULL;
	}
	return conn;
}


#endif
