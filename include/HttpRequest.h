//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_HTTPREQUEST_H
//#define WEB_SERVER_DEVELOPING_HTTPREQUEST_H

#pragma once

#include <iostream>
#include <unordered_map>


class HttpRequest;

std::ostream  &operator<<(std::ostream &, const HttpRequest &);     //重载输出操作符，具体定义在源文件中


struct HttpRequest {

    friend std::ostream  &operator<<(std::ostream &, const HttpRequest &);  //指定为友元函数

    enum HTTP_VERSION {     //版本枚举集合
        HTTP_10 = 0, HTTP_11, VERSION_NOT_SUPPORT
    };

    enum HTTP_METHOD {      //方法枚举集合，目前DELETE尚未实现
        GET = 0, POST, PUT, DELETE, METHOD_NOT_SUPPORT
    };

    enum HTTP_HEADER {      //头部字段枚举集合
        Host = 0,
        User_Agent,
        Connection,
        Accept_Encoding,
        Accept_Language,
        Accept,
        Cache_Control,
        Upgrade_Insecure_Requests
    };

    struct EnumClassHash {      //散列算法的实现，用来对HTTP_HEADER进行处理
        template<typename T>
        std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);     //把对应值强行解释为size_t类型作为哈希值
        }
    };

    static std::unordered_map<std::string, HTTP_HEADER> header_map;     //定义一个静态的头部字段映射表

    HttpRequest(std::string url = std::string(""), HTTP_METHOD method = METHOD_NOT_SUPPORT, HTTP_VERSION version = VERSION_NOT_SUPPORT) :   //构造函数
    mMethod(method), mVersion(version), mUri(url), mContent(nullptr),
    mHeaders(std::unordered_map<HTTP_HEADER, std::string, EnumClassHash>()) {};


    HTTP_METHOD mMethod;
    HTTP_VERSION mVersion;
    std::string mUri;
    char *mContent;
    std::unordered_map<HTTP_HEADER, std::string, EnumClassHash> mHeaders;
};


//#endif //WEB_SERVER_DEVELOPING_HTTPREQUEST_H
