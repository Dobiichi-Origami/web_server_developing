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
    MimeType(const std::string &str) : type(str) {}
    MimeType(const char *str) : type(str) {}

    std::string type;
};

extern std::unordered_map<std::string, MimeType> Mime_map;


class HttpResponse {

public:
    enum HttpStatusCode {
        Unknow,
        k200Ok = 200,
        k403Forbidden = 403,
        k404NotFound = 404,
        k500InternalFault = 500
    };

    explicit HttpResponse(bool mKeep = true) : mStatusCode(Unknow), keep_alive(mKeep), mMime("text/html"),
        mBody(nullptr), mVersion(HttpRequest::HTTP_11) {};

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
    HttpStatusCode mStatusCode;
    HttpRequest::HTTP_VERSION mVersion;
    std::string mStatusMsg;
    MimeType mMime;
    const char *mBody;
    std::string mFilePath;
    int mContentLength;
    bool keep_alive;
    std::unordered_map<std::string, std::string> mHeaders;
};

//#endif //WEB_SERVER_DEVELOPING_HTTPRESPONSE_H
