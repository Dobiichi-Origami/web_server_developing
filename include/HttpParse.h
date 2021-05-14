//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_HTTPPARSE_H
//#define WEB_SERVER_DEVELOPING_HTTPPARSE_H

#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#define CR '\r'
#define LF '\n'
#define LINE_END '\0'
#define PASS


class HttpRequest;

std::ostream &operator<<(std::ostream &, const HttpRequest &);  //重载输出操作符，并未实现

class HttpRequestParser {
public:
    enum LINE_STATE {   //行状态枚举集合
        LINE_OK = 0, LINE_BAD, LINE_MORE
    };

    enum PARSE_STATE {  //解析状态枚举集合
        PARSE_REQUESTLINE = 0, PARSE_HEADER, PARSE_BODY
    };

    enum HTTP_CODE {    //HTTP状态码枚举集合
        NO_REQUEST, GET_REQUEST, BAD_REQUEST, FORBIDDEN_REQUEST, INTERNAL_ERROR, CLOSED_CONNECTION
    };

    static LINE_STATE parse_line(char *buffer, int &checked_index, int &read_index);    //解析某一行

    static HTTP_CODE parse_requestline(char *line, PARSE_STATE &parse_state, HttpRequest &request);     //解析请求行

    static HTTP_CODE parse_headers(char *line, PARSE_STATE &parse_state, HttpRequest &request);     //解析请求头

    static HTTP_CODE parse_body(char *body, HttpRequest &request);      //解析请求体

    static HTTP_CODE parse_content(char *buffer, int &check_index, int &read_index, PARSE_STATE &parse_state,
            int &start_line, HttpRequest &request);     //解析请求内容
};

//#endif //WEB_SERVER_DEVELOPING_HTTPPARSE_H
