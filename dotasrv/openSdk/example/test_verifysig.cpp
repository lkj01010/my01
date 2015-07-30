/**
 * OpenAPI V3 SDK 示例代码，用于验证验证回调发货URL的签名
 *  http://wiki.open.qq.com/wiki/%E5%9B%9E%E8%B0%83%E5%8F%91%E8%B4%A7URL%E7%9A%84%E5%8D%8F%E8%AE%AE%E8%AF%B4%E6%98%8E_V3
 *
 * @version 3.0.0
 * @author open.qq.com
 * @copyright (c) 2013, Tencent Corporation. All rights reserved.
 * @History:
 *               3.0.0 | jixingguan | 2013-05-07 10:20:12 | initialization
 */

#include "OpenApiV3.h"
int main()
{
    map<string,string> params;

    //参数的含义请参考 http://wiki.open.qq.com/wiki/%E5%9B%9E%E8%B0%83%E5%8F%91%E8%B4%A7URL%E7%9A%84%E5%8D%8F%E8%AE%AE%E8%AF%B4%E6%98%8E_V3
    params["amt"]="80";
    params["appid"]="33758";
    params["billno"]="-APPDJT18700-20120210-1428215572";
    params["openid"]="test001" ;
    params["payamt_coins"]="20";
    params["payitem"]="323003*8*1";
    params["ts"]="1328855301";
    params["providetype"]="0";
    params["pubacct_payamt_coins"]="10";
    params["token"]="53227955F80B805B50FFB511E5AD51E025360";
    params["version"]="v3";
    params["zoneid"]="1";

    string appkey="12345f9a47df4d1eaeb3bad9a7e54321";
    unsigned int appid=33758;
    COpenApiV3 sdk(appid, appkey);      
    sdk.init();

    string url_path = "/cgi-bin/temp.py";
    string sig ="VvKwcaMqUNpKhx0XfCvOqPRiAnU=";
   
    bool iRet=sdk.verifySig(OPEN_API_V3_METHOD_GET,url_path,params,sig);
    if(iRet)
    {
        printf("sig=%s is valid\n",sig.c_str());
    }
    else
    {
        printf("sig=%s is invalid\n",sig.c_str());      
    }
    return 0;    
}
