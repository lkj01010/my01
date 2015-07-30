/**
 * OpenAPI V3 SDK 示例代码，适用于大部分OpenAPI。如果是上传文件类OpenAPI，请参考本SDK包中的“Test_UploadFile.cpp”文件中的示例代码。
 *
 * @version 3.0.0
 * @author open.qq.com
 * @copyright (c) 2013, Tencent Corporation. All rights reserved.
 * @History:
 *               3.0.0 | jixingguan | 2013-05-07 10:20:12 | initialization
 */


#include "OpenApiV3.h"

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

/***********************************************************
**函数名 get_user_info
**输入:   
**          sdk  
**          openid :
**          openkey:  
**          PF
**
**输出:  JsonRes  请求响应包
**              
**返回:无
**描述:
**           调用/v3/user/get_info接口
**************************************************************/

int get_user_info(class OpenApiV3* sdk, string& openid, string& openkey, string& pf,Json::Value& JsonRes)
{
    map<string,string> params;
    string script_name;

    params["openid"]=openid;
    params["openkey"]=openkey;
    params["pf"]=pf;

	script_name = "/v3/user/get_info";
    
	
	return sdk->api(script_name, params,JsonRes);	
}


/***********************************************************
**函数名 get_user_info_parse
**输入:   
                JsonRes  回应的json报文

**输出:  Info 解析后的结构 
**              
**返回:无
**描述:
**           调用/v3/user/get_info接口,
               示例怎样对JSON格式的报文进行解析
**************************************************************/

int get_user_info_parse(Json::Value& JsonRes ,struct userinfo& Info)
{

    Info.ret= JsonRes["ret"].asInt();
    if( 0 == Info.ret)
    {
        Info.is_lost= JsonRes["is_lost"].asInt();
        Info.nickname = JsonRes["nickname"].asString();
        Info.gender =  JsonRes["gender"].asString();
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


//----------------------------
struct buy_rsp{
    int ret;
    
};

// int buy_playzone_item(class OpenApiV3* sdk, string& openid, string& openkey, int zoneid, int count, Json::Value& JsonRes)
// {
//     map<string,string> params;
//     string script_name;

//     params["openid"]=openid;
//     params["openkey"]=openkey;
//     params["zoneid"]=zoneid;
//     params["itemid"]=itemid;
//     params["count"]=count;

//     script_name = "/v3/user/get_info";
    
    
//     return sdk->api(script_name, params,JsonRes);   
// }

// int buy_playzone_item_parse(Json::Value& JsonRes ,struct buy_rsp& Info)
// {

//     Info.ret= JsonRes["ret"].asInt();
//     if( 0 == Info.ret)
//     {
//         Info.is_lost= JsonRes["is_lost"].asInt();
//         Info.nickname = JsonRes["nickname"].asString();
//         Info.gender =  JsonRes["gender"].asString();
//         Info.country = JsonRes["country"].asString();
//         Info.province = JsonRes["province"].asString();
//         Info.city = JsonRes["city"].asString();
//         Info.figureurl = JsonRes["figureurl"].asString();
//         Info.is_yellow_vip = JsonRes["is_yellow_vip"].asInt();
//         Info.is_yellow_year_vip = JsonRes["is_yellow_year_vip"].asInt();
//         Info.yellow_vip_level = JsonRes["yellow_vip_level"].asInt();
//         Info.is_yellow_high_vip = JsonRes["is_yellow_high_vip"].asInt();
//     }    
//     return 0;
// }


int main(int argc,char** argv)
{
    //参数的传递可以看同名的脚本文件
    if( argc < 7)
    {
        printf("usage ./testopenapi appid appkey server_name openid openkey pf\n");
        return 0;
    }

    // 应用基本信息
    unsigned int appid = strtoul(argv[1],NULL,10);
    string appkey = argv[2];

    // OpenAPI的服务器IP 
    // 最新的API服务器地址请参考wiki文档: http://wiki.open.qq.com/wiki/API3.0%E6%96%87%E6%A1%A3 
    string server_name = argv[3];

    // 用户的OpenID/OpenKey
    string openid=argv[4];
    string openkey = argv[5];

    //test
    openid = "B1D43980E13A9C90F74F2C7405AE54A8";
    openkey = "E00862A8D31509B8AD3E0D90A5BC94E5";

    // 所要访问的平台, pf的其他取值参考wiki文档: http://wiki.open.qq.com/wiki/API3.0%E6%96%87%E6%A1%A3 
    string pf =argv[6];

    pf = "wanba_pf";
    
    COpenApiV3 sdk(appid, appkey);      
    //对象初始化，设置服务器地址
    sdk.init();
    sdk.setServerName(server_name);
    sdk.setDebugSwitch(true);    
   
    Json::Value JsonRes;  
    struct userinfo Info;
    int iRet=get_user_info(&sdk, openid, openkey, pf,JsonRes);
    if( 0 != iRet)
    {
        printf("iRet=%d err:%s\n",iRet,sdk.GetErrMsg());
    }
    else
    {
        //对返回的信息进行解析
        get_user_info_parse(JsonRes,Info);
        printf("Info.ret=%d\n",Info.ret);
        printf("Info.is_lost=%d\n",Info.is_lost);
        printf("Info.nickname=%s\n",Info.nickname.c_str());
        printf("Info.country=%s\n",Info.country.c_str());
        printf("Info.province=%s\n",Info.province.c_str());
        printf("Info.city=%s\n",Info.city.c_str());
        printf("Info.figureurl=%s\n",Info.figureurl.c_str());
        printf("Info.is_yellow_vip=%d\n",Info.is_yellow_vip);
        printf("Info.is_yellow_year_vip=%d\n",Info.is_yellow_year_vip);
        printf("Info.yellow_vip_level=%d\n",Info.yellow_vip_level);
        printf("Info.is_yellow_high_vip=%d\n",Info.is_yellow_high_vip);
    }
    return 0;
} 

