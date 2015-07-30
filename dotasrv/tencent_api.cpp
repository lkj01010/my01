#include "tencent_api.h"

using namespace std;
#if defined _LINUX

#include "openSdk/tencent_sdk_lib/include/http_request_helper.h"
#include "openSdk/tencent_sdk_lib/include/openapi_comm_def.h"
#include "openSdk/tencent_sdk_lib/include/OpenApiUdpClient.h"
#include "openSdk/tencent_sdk_lib/include/OpenApiV3.h"
#include "openSdk/tencent_sdk_lib/include/SnsSigCheck.h"
#include "openSdk/tencent_sdk_lib/include/SnsStat.h"
#include "openSdk/tencent_sdk_lib/include/uri_new.h"

static const string s_appid = "1104680669";
static const string s_appkey = "M6TOzozadY9AK8ug";
static const string s_server_name = "119.147.19.43";

int get_user_info(class OpenApiV3* sdk, string& openid, string& openkey, string& pf, Json::Value& JsonRes)
{
	map<string, string> params;
	string script_name;

	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;

	script_name = "/v3/user/get_info";

	return sdk->api(script_name, params, JsonRes);
}

int get_user_info_parse(Json::Value& JsonRes ,struct userinfo& Info)
{
	Info.ret = JsonRes["ret"].asInt();
	if (0 == Info.ret)
	{
		Info.is_lost = JsonRes["is_lost"].asInt();
		Info.nickname = JsonRes["nickname"].asString();
		Info.gender = JsonRes["gender"].asString();
		Info.country = JsonRes["country"].asString();
		Info.province = JsonRes["province"].asString();
		Info.city = JsonRes["city"].asString();
		Info.figureurl = JsonRes["figureurl"].asString();
		Info.is_yellow_vip = JsonRes["is_yellow_vip"].asInt();
		Info.is_yellow_year_vip = JsonRes["is_yellow_year_vip"].asInt();
		Info.yellow_vip_level = JsonRes["yellow_vip_level"].asInt();
		Info.is_yellow_high_vip = JsonRes["is_yellow_high_vip"].asInt();
	}
	return 0;
}


#endif


tencent_api::tencent_api()
{
#if defined _LINUX
	COpenApiV3 sdk(s_appid, s_appkey);

	sdk.init();
	sdk.setServerName(s_server_name);
	sdk.setDebugSwitch(true);
#endif
}


tencent_api::~tencent_api()
{
}
