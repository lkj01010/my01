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

// struct  userinfo
// {
//     int ret;
//     int is_lost;
//     string nickname;
//     string gender;
//     string country;
//     string province;
//     string city;
//     string figureurl;
//     int is_yellow_vip;
//     int is_yellow_year_vip;
//     int yellow_vip_level;
//     int is_yellow_high_vip;
//     userinfo()
// 	{
//         ret =0;
// 		is_lost = 0;
// 		is_yellow_vip =0;
// 		is_yellow_year_vip=0;
// 		yellow_vip_level=0;
// 		is_yellow_high_vip=0;
// 	}
// };


struct playzone_userinfo{
	int code;
	int subcode;
	string message;
	bool is_vip;
	int vip_level;
	int score;
	int expiredtime;
};

int get_playzone_userinfo(class OpenApiV3* sdk, string& openid, string& openkey, string& pf, Json::Value& JsonRes)
{
	map<string, string> params;
	string script_name;

	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;

	script_name = "/v3/user/get_playzone_userinfo";

	return sdk->api(script_name, params, JsonRes);
}

int get_playzone_userinfo_parse(Json::Value& JsonRes ,struct playzone_userinfo& Info)
{
	Info.code = JsonRes["cdoe"].asInt();
	if (0 == Info.code)
	{
		Info.subcode = JsonRes["subcode"].asInt();
		Info.message = JsonRes["message"].asString();

		Json::Value data_array = value["data"];  

		Info.is_vip = data_array[0]["msg"].asBool();	//lkj can?
		Info.vip_level = data_array[0]["vip_level"].asInt();
		Info.score = data_array[0]["score"].asInt();
		Info.expiredtime = data_array[0]["expiredtime"].asInt();
	}
	return 0;
}

//-----------------------------------------------

struct buy_playzone_item{
	int code;
	int subcode;
	string message;
	int billno;
	int cost;
};

int get_buy_playzone_item(class OpenApiV3* sdk, string& openid, string& openkey, string& pf, Json::Value& JsonRes)
{
	map<string, string> params;
	string script_name;

	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;

	script_name = "/v3/user/buy_playzone_item";

	return sdk->api(script_name, params, JsonRes);
}

int get_playzone_userinfo_parse(Json::Value& JsonRes ,struct playzone_userinfo& Info)
{
	Info.code = JsonRes["cdoe"].asInt();
	if (0 == Info.code)
	{
		Info.subcode = JsonRes["subcode"].asInt();
		Info.message = JsonRes["message"].asString();

		Json::Value data_array = value["data"];  

		Info.billno = data_array[0]["billno"].asInt();
		Info.cost = data_array[0]["cost"].asInt();
	}
	return 0;
}




// int get_user_info(class OpenApiV3* sdk, string& openid, string& openkey, string& pf, Json::Value& JsonRes)
// {
// 	map<string, string> params;
// 	string script_name;

// 	params["openid"] = openid;
// 	params["openkey"] = openkey;
// 	params["pf"] = pf;

// 	script_name = "/v3/user/get_info";

// 	return sdk->api(script_name, params, JsonRes);
// }

// int get_user_info_parse(Json::Value& JsonRes ,struct userinfo& Info)
// {
// 	Info.ret = JsonRes["ret"].asInt();
// 	if (0 == Info.ret)
// 	{
// 		Info.is_lost = JsonRes["is_lost"].asInt();
// 		Info.nickname = JsonRes["nickname"].asString();
// 		Info.gender = JsonRes["gender"].asString();
// 		Info.country = JsonRes["country"].asString();
// 		Info.province = JsonRes["province"].asString();
// 		Info.city = JsonRes["city"].asString();
// 		Info.figureurl = JsonRes["figureurl"].asString();
// 		Info.is_yellow_vip = JsonRes["is_yellow_vip"].asInt();
// 		Info.is_yellow_year_vip = JsonRes["is_yellow_year_vip"].asInt();
// 		Info.yellow_vip_level = JsonRes["yellow_vip_level"].asInt();
// 		Info.is_yellow_high_vip = JsonRes["is_yellow_high_vip"].asInt();
// 	}
// 	return 0;
// }


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

const std::string& tencent_api::handle_request(const std::string& request){
    return "hello tencent api";
}