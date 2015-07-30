#pragma once

#include "com/common.h"

class tencent_api
{
public:
	tencent_api();
	~tencent_api();

    const std::string& handle_request(const std::string& request);
};

