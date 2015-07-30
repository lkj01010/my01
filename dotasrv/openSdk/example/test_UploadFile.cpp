/**
 * OpenAPI V3 SDK 示例代码，上传文件类接口示例代码。适用于所有需要发送multipart/form-data格式的post请求的OpenAPI
 * @version 3.0.0
 * @author open.qq.com
 * @copyright (c)2013, Tencent Corporation. All rights reserved.
 * @History:/Users/Midstream/Documents/Dev/network/tecent-h5-sdk/C++_SDK_V3.0.1/example/test_verifysig.cpp
 *               3.0.0 | jixingguan | 2013-05-16 10:20:12 | initialization
 */


#include "OpenApiV3.h"
#include "json/json.h"

/*发表带图片的微博*/
int add_weibo_pic(class OpenApiV3* sdk, string& openid, string& openkey, string& pf,Json::Value& JsonRes)
{
    map<string,string> params;
    string script_name;

    params["openid"]=openid;
    params["openkey"]=openkey;
    params["pf"]=pf;
    params["content"]="hello world";

	script_name = "/v3/t/add_pic_t";    
	struct FormFileElement fileparam;
	
	fileparam.field_name="pic";
	fileparam.file_full_name="photo/test.jpg";
	
	return sdk->apiUploadFile(script_name, params,JsonRes,fileparam);	
}


int main(int argc,char** argv)
{
    int iRet=0;
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

    // 所要访问的平台, pf的其他取值参考wiki文档: http://wiki.open.qq.com/wiki/API3.0%E6%96%87%E6%A1%A3 
    string pf =argv[6];
    
    //创建opeapiv3 的访问类
    COpenApiV3 sdk(appid, appkey);      

    //进行初始化，设置服务器地址
    sdk.init();
    sdk.setServerName(server_name);
    sdk.setDebugSwitch(true);
   
   Json::Value JsonRes;     
   iRet=add_weibo_pic(&sdk, openid, openkey, pf,JsonRes);
   if( 0 != iRet)
   {
        printf("add_weibo_pic failed iRet=%d err:%s\n",iRet,sdk.GetErrMsg());
   }
   else
   {
        printf("add_weibo_pic sucess\n");
   }
   return 0;
} 
