#pragma once

#include "com/common.h"

static const std::string k_playzone_userinfo ="k_playzone_userinfo";
static const std::string k_userinfo ="k_userinfo";
static const std::string k_buy_playzone_item = "k_buy_playzone_item";

#if defined _LINUX

#include "openSdk/tencent_sdk_lib/include/http_request_helper.h"
#include "openSdk/tencent_sdk_lib/include/openapi_comm_def.h"
#include "openSdk/tencent_sdk_lib/include/OpenApiUdpClient.h"
#include "openSdk/tencent_sdk_lib/include/OpenApiV3.h"
#include "openSdk/tencent_sdk_lib/include/SnsSigCheck.h"
#include "openSdk/tencent_sdk_lib/include/SnsStat.h"
#include "openSdk/tencent_sdk_lib/include/uri_new.h"
#endif

class tencent_api
{
public:
	tencent_api();
	~tencent_api();

	const std::string handle_request(std::string openid, std::string openkey,
		std::string platform, std::string api);

private:

 #ifdef _LINUX 
	COpenApiV3 *sdk_;
#endif 

};

