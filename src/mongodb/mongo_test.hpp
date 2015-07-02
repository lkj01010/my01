#pragma once
#include "mongo_wrapper.h"

#ifndef verify
#  define verify(x) MONGO_verify(x)
#endif

namespace my{
	using namespace mongo;
	using namespace std;
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

	inline int test_second(){
		boost::scoped_ptr<DBClientBase> conn(mongo_wrapper::instance().connect());
		const char * ns = "test.second";

		conn->remove(ns, BSONObj());

		conn->insert(ns, BSON("name" << "eliot" << "num" << 17));
		conn->insert(ns, BSON("name" << "sara" << "num" << 24));

		std::auto_ptr<DBClientCursor> cursor = conn->query(ns, BSONObj());

		if (!cursor.get()) {
			cout << "query failure" << endl;
			return EXIT_FAILURE;
		}

		cout << "using cursor" << endl;
		while (cursor->more()) {
			BSONObj obj = cursor->next();
			cout << "\t" << obj.jsonString() << endl;
		}

		conn->createIndex(ns, BSON("name" << 1 << "num" << -1));

		///////////////////////////////////////////////
		cout << "now using $where" << endl;

		Query q = Query("{}").where("this.name == name", BSON("name" << "sara"));

		cursor = conn->query(ns, q);
		if (!cursor.get()) {
			cout << "query failure" << endl;
			return EXIT_FAILURE;
		}

		int num = 0;
		while (cursor->more()) {
			BSONObj obj = cursor->next();
			cout << "\t" << obj.jsonString() << endl;
			num++;
		}
		verify(num == 1);

		return EXIT_SUCCESS;
	}
}
