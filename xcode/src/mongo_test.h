#pragma once
#include "common.h"

using namespace mongo;

namespace mongoc{

	inline void insert(DBClientBase* conn, const char * name, int num) {
		BSONObjBuilder obj;
		obj.append("name", name);
		obj.append("num", num);
		conn->insert("test.people", obj.obj());
		std::string e = conn->getLastError();
		if (!e.empty()) {
			std::cout << "insert failed: " << e << std::endl;
			exit(NULL);
		}
	}
	inline boost::shared_ptr<DBClientBase> mongo_init(){
		mongo::client::GlobalInstance instance;
		if (!instance.initialized()) {
			std::cout << "failed to initialize the client driver: " << instance.status() << std::endl;
			return NULL;
		}

		std::string uri = "mongodb://localhost:27017";
		std::string errmsg;

		ConnectionString cs = ConnectionString::parse(uri, errmsg);

		if (!cs.isValid()) {
			std::cout << "Error parsing connection string " << uri << ": " << errmsg << std::endl;
			return NULL;
		}

		boost::shared_ptr<DBClientBase> conn(cs.connect(errmsg));
		if (!conn) {
			std::cout << "couldn't connect : " << errmsg << std::endl;
			return NULL;
		}


		{
			// clean up old data from any previous tests
			BSONObjBuilder query;
			conn->remove("test.people", query.obj());
		}

		//insert(conn.get(), "eliot", 15);
		//insert(conn.get(), "sara", 23);

		return conn;
	}
}
