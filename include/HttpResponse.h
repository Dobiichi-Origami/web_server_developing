//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_HTTPRESPONSE_H
//#define WEB_SERVER_DEVELOPING_HTTPRESPONSE_H

#pragma once

#include "HttpRequest.h"

#include <string>
#include <unordered_map>
#include <memory>


struct MimeType {

    // 根据string和char *进行构造MimeType
    // 在这里，MimeType可以被隐式构造
    MimeType(const std::string &str) : type(str) {}
    MimeType(const char *str) : type(str) {}

    std::string type;
};

extern std::unordered_map<std::string, MimeType> Mime_map;  // 构造外部可访问的Mime_map


class HttpResponse {

public:
    enum HttpStatusCode {   // HTTP状态码枚举集合
        Unknow,
        k200Ok = 200,
        k403Forbidden = 403,
        k404NotFound = 404,
        k500InternalFault = 500
    };

    // 必须显式初始化HttpResponse对象，默认参数已写
    explicit HttpResponse(bool mKeep = true) : mStatusCode(Unknow), keep_alive(mKeep), mMime("text/html"),
        mBody(nullptr), mVersion(HttpRequest::HTTP_11) {};

    // 一堆Getter和Setter
    HttpStatusCode getMStatusCode() const {
        return mStatusCode;
    }

    void setMStatusCode(HttpStatusCode mStatusCode) {
        HttpResponse::mStatusCode = mStatusCode;
    }

    HttpRequest::HTTP_VERSION getMVersion() const {
        return mVersion;
    }

    void setMVersion(HttpRequest::HTTP_VERSION mVersion) {
        HttpResponse::mVersion = mVersion;
    }

    const std::string &getMStatusMsg() const {
        return mStatusMsg;
    }

    void setMStatusMsg(const std::string &mStatusMsg) {
        HttpResponse::mStatusMsg = mStatusMsg;
    }

    const MimeType &getMMime() const {  //新加入
        return mMime;
    }

    void setMMime(const MimeType &mMime) {
        HttpResponse::mMime = mMime;
    }

    const char *getMBody() const {  //新加入
        return mBody;
    }

    void setMBody(const char *mBody) {
        HttpResponse::mBody = mBody;
    }

    const std::string &getMFilePath() const {
        return mFilePath;
    }

    void setMFilePath(const std::string &mFilePath) {
        HttpResponse::mFilePath = mFilePath;
    }

    int getMContentLength() const { //新加入
        return mContentLength;
    }

    void setMContentLength(int mContentLength) {
        HttpResponse::mContentLength = mContentLength;
    }

    bool isKeepAlive() const {
        return keep_alive;
    }

    void setKeepAlive(bool keepAlive) {
        keep_alive = keepAlive;
    }

    void addHeader(const std::string &key, const std::string &value) {
        mHeaders[key] = value;
    }

    void appendBuffer(char *) const;

private:
    HttpStatusCode mStatusCode;     // 响应状态码
    HttpRequest::HTTP_VERSION mVersion;     // 响应的HTTP版本
    std::string mStatusMsg;     // 状态解释性信息
    MimeType mMime;     // 返回的Mime类型
    const char *mBody;      // 返回体中的body
    std::string mFilePath;  // 文件路径
    int mContentLength;     // 包含的内容的长度
    bool keep_alive;    // 是否保持链接
    std::unordered_map<std::string, std::string> mHeaders;  //  头部字段
};

//#endif //WEB_SERVER_DEVELOPING_HTTPRESPONSE_H
