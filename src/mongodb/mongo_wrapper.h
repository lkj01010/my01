#pragma once
#include "common.h"
#include "mongo/client/dbclient.h"

namespace my{
	class mongo_wrapper : public singleton<mongo_wrapper>
	{
	public:
		mongo_wrapper();
		~mongo_wrapper();

		mongo::DBClientBase*connect(const string& url = "mongodb://localhost:27017");

	public:
		mongo::client::GlobalInstance instance_;
	};
}

