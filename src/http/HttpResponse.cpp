//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../../include/HttpResponse.h"

#include <string>

std::unordered_map<std::string, MimeType> Mime_map = {  // 赋值Mime_map，其中MimeType对象为隐式调用了其构造函数生成
        {".html", "text/html"},
        {".xml", "text/xml"},
        {".xhtml", "application/xhtml+xml"},
        {".txt", "text/plain"},
        {".rtf", "application/rtf"},
        {".pdf", "application/pdf"},
        {".word", "application/msword"},
        {".png", "image/png"},
        {".gif", "image/gif"},
        {".jpg", "image/jpeg"},
        {".jpeg", "image/jpeg"},
        {".au", "audio/basic"},
        {".mpeg", "video/mpeg"},
        {".mpg", "video/mpeg"},
        {".avi", "video/x-msvideo"},
        {".gz", "application/x-gzip"},
        {".tar", "application/x-tar"},
        {".css", "text/css"},
        {"", "text/plain"},
        {"default","text/plain"}
};


// 往buffer中添加该response的信息
void HttpResponse::appendBuffer(char *buffer) const{

    // 版本
    if (mVersion == HttpRequest::HTTP_11) {
        sprintf(buffer, "HTTP/1.1 %d %s\r\n", mStatusCode, mStatusMsg.c_str());
    } else {
        sprintf(buffer, "HTTP/1.0 %d %s\r\n", mStatusCode, mStatusMsg.c_str());
    }
    // 头部字段
    for (auto it = mHeaders.begin(); it != mHeaders.end(); it++) {
        sprintf(buffer, "%s%s: %s\r\n", buffer, it->first.c_str(), it->second.c_str());
    }
    sprintf(buffer, "%sContent-type: %s\r\n", buffer, mMime.type.c_str());
    // keep_alive
    if (keep_alive) {
        sprintf(buffer, "%sConnection: keep-alive\r\n", buffer);
    } else {
        sprintf(buffer, "%sConnection: close\r\n", buffer);
    }
}