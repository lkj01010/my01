



#if defined _LINUX

#include "tencent_api.h"
#include <boost/lexical_cast.hpp>

using namespace std;

static const string s_appid = "1104680669";
static string s_appkey = "M6TOzozadY9AK8ug";
// static string s_server_name = "119.147.19.43";
static string s_server_name = "openapi.tencentyun.com";



struct playzone_userinfo{
	int code;
	int subcode;
	string message;
	bool is_vip;
	int vip_level;
	int score;
	int expiredtime;

	playzone_userinfo()
		: code(0)
		, subcode(0)
		, message("")
		, is_vip(false)
		, vip_level(0)
		, score(0)
		, expiredtime(0)
		{}
};

int get_playzone_userinfo(class OpenApiV3* sdk, const string& openid, const string& openkey, const string& pf, Json::Value& JsonRes)
{
	map<string, string> params;
	string script_name;

	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;

	script_name = "/v3/user/get_playzone_userinfo";

	SLOG_DEBUG << "do sdk->api";
	return sdk->api(script_name, params, JsonRes);
}

int get_playzone_userinfo_parse(Json::Value& JsonRes ,struct playzone_userinfo& Info)
{
	Info.code = JsonRes["code"].asInt();				SLOG_DEBUG << " code=" << Info.code;
	// if (0 == Info.code)
	// {
		Info.subcode = JsonRes["subcode"].asInt();		SLOG_DEBUG << " subcode=" << Info.subcode;
		Info.message = JsonRes["message"].asString();		SLOG_DEBUG << " message=" << Info.message;

		const Json::Value arrayObj = JsonRes["data"];  
		int i = 0;
		const Json::Value& data = arrayObj[i];

		Info.is_vip = data["msg"].asBool();				SLOG_DEBUG << " is_vip=" << Info.is_vip;
		Info.vip_level = data["vip_level"].asInt();		SLOG_DEBUG << " vip_level=" << Info.vip_level;
		Info.score = data["score"].asInt();				SLOG_DEBUG << " score=" << Info.score;
		Info.expiredtime = data["expiredtime"].asInt();	SLOG_DEBUG << " expiredtime=" << Info.expiredtime;
	// }
	return 0;
}


//-----------------------------------------------

struct buy_playzone_item {
	int code;
	int subcode;
	string message;
	
	int billno;
	int cost;

	buy_playzone_item()
		: code(0)
		, subcode(0)
		, message("")
		, billno(0)
		, cost(0)
		{}
};

int get_buy_playzone_item(class OpenApiV3* sdk, const string& openid, const string& openkey, const string& pf, Json::Value& JsonRes)
{
	map<string, string> params;
	string script_name;

	params["openid"] = openid;
	params["openkey"] = openkey;
	params["pf"] = pf;

	script_name = "/v3/user/buy_playzone_item";

	SLOG_DEBUG << "do sdk->buy_playzone_item";
	return sdk->api(script_name, params, JsonRes);
}

int get_buy_playzone_item_parse(Json::Value& JsonRes ,struct buy_playzone_item& Info)
{
	Info.code = JsonRes["code"].asInt();				SLOG_DEBUG << " code=" << Info.code;
	// if (0 == Info.code)
	// {
		Info.subcode = JsonRes["subcode"].asInt();		SLOG_DEBUG << " subcode=" << Info.subcode;
		Info.message = JsonRes["message"].asString();		SLOG_DEBUG << " message=" << Info.message;

		const Json::Value arrayObj = JsonRes["data"];  
		int i = 0;
		const Json::Value& data = arrayObj[i];

		Info.billno = data["billno"].asBool();				SLOG_DEBUG << " billno=" << Info.billno;
		Info.cost = data["cost"].asInt();					SLOG_DEBUG << " cost=" << Info.cost;
	// }
	return 0;
}



//-----------------------------------------------

// struct buy_playzone_item{
// 	int code;
// 	int subcode;
// 	string message;
// 	int billno;
// 	int cost;
// };

// int get_buy_playzone_item(class OpenApiV3* sdk, string& openid, string& openkey, string& pf, Json::Value& JsonRes)
// {
// 	map<string, string> params;
// 	string script_name;

// 	params["openid"] = openid;
// 	params["openkey"] = openkey;
// 	params["pf"] = pf;

// 	script_name = "/v3/user/buy_playzone_item";

// 	return sdk->api(script_name, params, JsonRes);
// }

// int get_buy_playzone_parse(Json::Value& JsonRes ,struct playzone_userinfo& Info)
// {
// 	Info.code = JsonRes["code"].asInt();
// 	if (0 == Info.code)
// 	{
// 		Info.subcode = JsonRes["subcode"].asInt();
// 		Info.message = JsonRes["message"].asString();

// 		Json::Value& data_array = value["data"];  
// 		Json::Value& data = data_array[0];

// 		Info.billno = data["billno"].asInt();
// 		Info.cost = data["cost"].asInt();
// 	}
// 	return 0;
// }
//--------------------------------------------------------------------

struct  userinfo
{
    int ret;
    int is_lost;
    string nickname;
    string gender;
    string country;
    string province;
    string city;
    string figureurl;
    int is_yellow_vip;
    int is_yellow_year_vip;
    int yellow_vip_level;
    int is_yellow_high_vip;
    userinfo()
	{
        ret =0;
		is_lost = 0;
		is_yellow_vip =0;
		is_yellow_year_vip=0;
		yellow_vip_level=0;
		is_yellow_high_vip=0;
	}
};


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
	// if (0 == Info.ret)
	{
		Info.is_lost = JsonRes["is_lost"].asInt();							SLOG_DEBUG << " is_lost=" << Info.is_lost;
		Info.nickname = JsonRes["nickname"].asString();						SLOG_DEBUG << " nickname=" << Info.nickname;
		Info.gender = JsonRes["gender"].asString();							SLOG_DEBUG << " gender=" << Info.gender;
		Info.country = JsonRes["country"].asString();						SLOG_DEBUG << " country=" << Info.country;
		Info.province = JsonRes["province"].asString();						SLOG_DEBUG << " province=" << Info.province;			
		Info.city = JsonRes["city"].asString();								SLOG_DEBUG << " city=" << Info.city;	
		Info.figureurl = JsonRes["figureurl"].asString();					SLOG_DEBUG << " figureurl=" << Info.figureurl;
		Info.is_yellow_vip = JsonRes["is_yellow_vip"].asInt();				SLOG_DEBUG << " is_yellow_vip=" << Info.is_yellow_vip;
		Info.is_yellow_year_vip = JsonRes["is_yellow_year_vip"].asInt();	SLOG_DEBUG << " is_yellow_year_vip=" << Info.is_yellow_year_vip;
		Info.yellow_vip_level = JsonRes["yellow_vip_level"].asInt();		SLOG_DEBUG << " yellow_vip_level=" << Info.yellow_vip_level;
		Info.is_yellow_high_vip = JsonRes["is_yellow_high_vip"].asInt();	SLOG_DEBUG << " is_vip=" << Info.is_yellow_high_vip;
	}
	return 0;
}

//----------------------------------------------------------

tencent_api::tencent_api()
{
	unsigned int appid = boost::lexical_cast<unsigned int>(s_appid);
	sdk_ = new COpenApiV3(appid, s_appkey);
	sdk_->init();
	sdk_->setServerName(s_server_name);
	sdk_->setDebugSwitch(true);
}

tencent_api::~tencent_api()
{
	delete sdk_;
	sdk_ = NULL;
}

const std::string tencent_api::handle_request(std::string openid, std::string openkey,
		std::string platform, std::string api){
	SLOG_DEBUG << "api: " << api;

	if (api == k_playzone_userinfo)
	{
		Json::Value JsonRes;  
    	struct playzone_userinfo Info;

    	SLOG_DEBUG << "begin get_playzone_userinfo"<< " openid=" << openid << " openkey=" << openkey << " platform=" << platform;
		int iRet = get_playzone_userinfo(sdk_, openid, openkey, platform, JsonRes);


		if (0 != iRet)
		{
			SLOG_INFO << "get_playzone_userinfo: fail. " ; 
			get_playzone_userinfo_parse(JsonRes,Info);
			return string("({\"is_ok\":0})");
		}
		else{
			get_playzone_userinfo_parse(JsonRes,Info);
			SLOG_INFO << "userinfo fetched: is_vip=" << Info.is_vip << " socre=" << Info.score << " expiredtime="
				<< Info.expiredtime;

			return string("({\"is_ok\":1") 
					 + string(",\"subcode\":") + boost::lexical_cast<string>(Info.subcode) 
					 + string(",\"is_vip\":") + boost::lexical_cast<string>(Info.is_vip)
					 + string(", \"vip_level\":") + boost::lexical_cast<string>(Info.vip_level)
					 + string(", \"score\":") + boost::lexical_cast<string>(Info.score)
					 + string(", \"expiredtime\":") + boost::lexical_cast<string>(Info.expiredtime)
					 + string("})");
		}
	}
	//------------------------------------------
	else if(api == k_buy_playzone_item){
		Json::Value JsonRes;  
    	struct buy_playzone_item Info;

    	SLOG_DEBUG << "begin get_playzone_userinfo"<< " openid=" << openid << " openkey=" << openkey << " platform=" << platform;
		int iRet = get_buy_playzone_item(sdk_, openid, openkey, platform, JsonRes);


		if (0 != iRet)
		{
			SLOG_INFO << "get_buy_playzone_item: fail. " ; 
			get_buy_playzone_item_parse(JsonRes,Info);
			return string("({\"is_ok\":0})");
		}
		else{
			get_buy_playzone_item_parse(JsonRes,Info);
			SLOG_INFO << "get_buy_playzone_item: billno=" << Info.billno << " socre=" << Info.cost ;
			return string("({\"is_ok\":1") 
					 + string(",\"subcode\":") + boost::lexical_cast<string>(Info.subcode) 
					 + string(",\"billno\":") + boost::lexical_cast<string>(Info.billno)
					 + string(", \"cost\":") + boost::lexical_cast<string>(Info.cost)
					 + string("})");
		}
	}
	//------------------------------------------
	else if (api == k_userinfo){
		Json::Value JsonRes;  
    	struct userinfo Info;

    	SLOG_DEBUG << "begin get_user_info"<< " openid=" << openid << " openkey=" << openkey << " platform=" << platform;
		int iRet = get_user_info(sdk_, openid, openkey, platform, JsonRes);
		get_user_info_parse(JsonRes, Info);
		if (0 != iRet)
		{
			SLOG_INFO << "get_user_info: fail." ; 
			return string("({\"is_ok\":0})");
		}
		else{
			SLOG_INFO << "get_user_info: success." ; 
			return "";
		}
	}
	else{
		SLOG_INFO << "undefined tencent api";
		return string("({\"is_ok\":0})");
	}
}

#else

#include "tencent_api.h"

tencent_api::tencent_api(){

}

tencent_api::~tencent_api()
{
}

const std::string tencent_api::handle_request(std::string openid, std::string openkey,
		std::string platform, std::string api){
	if (api == k_playzone_userinfo)
	{
		// Json::Value JsonRes;  
  //   	struct playzone_userinfo Info;

     	SLOG_DEBUG << "begin get_playzone_userinfo";
		// int iRet = get_playzone_userinfo(sdk_, openid, openkey, platform, JsonRes);
		// if (0 != iRet)
		// {
		// 	SLOG_INFO << "userinfo fetched: fail";
		// 	return string("({\"is_ok\":0})");
		// }
		// else{
		// 	get_playzone_userinfo_parse(JsonRes,Info);
		// 	SLOG_INFO << "userinfo fetched: is_vip=" << Info.is_vip << " socre=" << Info.score << " expiredtime="
		// 		<< Info.expiredtime;

		// 	return string("({\"is_ok\":1") 
		// 			 + string(",\"subcode\":") + boost::lexical_cast<string>(Info.subcode) 
		// 			 + string(",\"is_vip\":") + boost::lexical_cast<string>(Info.is_vip)
		// 			 + string(", \"vip_level\":") + boost::lexical_cast<string>(Info.vip_level)
		// 			 + string(", \"score\":") + boost::lexical_cast<string>(Info.score)
		// 			 + string(", \"expiredtime\":") + boost::lexical_cast<string>(Info.expiredtime)
		// 			 + string("})");
		// }
		return "";
	}
	else{
		return "";
	}
	
}

#endif
