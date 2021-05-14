//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../../include/HttpRequest.h"
#include "../../include/HttpParse.h"
#include "../../include/Util.h"

#include <cstring>
#include <algorithm>


std::unordered_map<std::string, HttpRequest::HTTP_HEADER> HttpRequest::header_map = {   //头部请求字段对应枚举值的查找表
        {"HOST",                      HTTP_HEADER::Host},
        {"USER-AGENT",                HTTP_HEADER::User_Agent},
        {"CONNECTION",                HTTP_HEADER::Connection},
        {"ACCEPT-ENCODING",           HTTP_HEADER::Accept_Encoding},
        {"ACCEPT-LANGUAGE",           HTTP_HEADER::Accept_Language},
        {"ACCEPT",                    HTTP_HEADER::Accept},
        {"CACHE-CONTROL",             HTTP_HEADER::Cache_Control},
        {"UPGRADE-INSECURE-REQUESTS", HTTP_HEADER::Upgrade_Insecure_Requests}
};


// 对整个缓冲区中的请求内容进行分行。
// buffer为整个请求所包含的内容，
// 参数中的checked_index为该行的起始字符的索引，在函数体中为当前解析的字符，
// read_index为buffer中下一个空位（等待数据插入）的索引。
HttpRequestParser::LINE_STATE HttpRequestParser::parse_line(char *buffer, int &checked_index, int &read_index) {
    char temp;  //字符缓冲
    for (; checked_index < read_index; checked_index++) {   //按顺序解析该行的内容
        temp = buffer[checked_index];   //读入内容
        if (temp == CR) {   //如果该字符为 \r
            if (checked_index + 1 == read_index)    //且该字符正好是当前缓冲区里最后一个字符
                return LINE_MORE;   //行未读完，还需要读取更多

            if (buffer[checked_index + 1] == LF) {      //如果该字符为 \n
                buffer[checked_index++] = LINE_END;     //将 \r 置为 \0
                buffer[checked_index++] = LINE_END;     //将 \n 置为 \0
                return LINE_OK;     //此时checked_index指向原本 \n 所在索引的下一个位置，即下一行的起始字符处。一行读取完毕
            }
            return LINE_BAD;    //意外情况，报错
        }
    }

    return LINE_MORE;   //还未读完一行
}

// 解析请求行的内容，
// line为请求行首字符的指针，
// parse_state指代当前解析进度，
// request为需要设置的请求实体。
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_requestline(char *line, PARSE_STATE &parse_state, HttpRequest &request) {
    char *url = strpbrk(line, " \t");   // 找到该行中第一个制表符出现的字符位置的地址
    if (!url) {     // 找不到则直接报错
        return BAD_REQUEST;
    }

    // 分割 method 和 url，将该制表符置为 \0，url指向所请求的文件目录字符串和后面的版本字符串
    *url++ = '\0';

    char *method = line;    // 此时line就是方法名

    if (strcasecmp(method, "GET") == 0) {   //匹配方法
        request.mMethod = HttpRequest::GET;
    } else if (strcasecmp(method, "POST") == 0) {
        request.mMethod = HttpRequest::POST;
    } else if (strcasecmp(method, "PUT") == 0) {
        request.mMethod = HttpRequest::PUT;
    } else if (strcasecmp(method, "DELETE") == 0) {
        request.mMethod = HttpRequest::DELETE;
    } else {
        return BAD_REQUEST;
    }

    // 如果在真正的URL字符串之前存在有多个制表符或者空格，则通过这个方法跳过这些符号
    // strspn返回一个索引，为目标字符串中第一个不属于参数2字符集的字符的索引
    url += strspn(url, " \t");

    char *version = strpbrk(url, " \t");    // 检索HTTP版本字符串的位置
    if (!version) {
        return BAD_REQUEST;
    }
    *version++ = '\0';
    version += strspn(version, " \t");      // 如上，跳过多余制表符与空行

    // 版本号后面可能还存在空白字符，需要手动指定匹配长度
    if (strncasecmp("HTTP/1.1", version, 8) == 0) {     // 设定HTTP版本号
        request.mVersion = HttpRequest::HTTP_11;
    } else if (strncasecmp("HTTP/1.0", version, 8) == 0) {
        request.mVersion = HttpRequest::HTTP_10;
    } else {
        return BAD_REQUEST;
    }

    if (strncasecmp(url, "http://", 7) == 0) {      // 如果url是一个完整的url
        url += 7;
        url = strchr(url, '/');     // 定位到uri起始处
    } else if (strncasecmp(url, "/", 1) == 0) {     // 如果url不完整，则直接查找是否存在第一个 /
        PASS;
    } else {
        return BAD_REQUEST;
    }

    if (!url || *url != '/') {      // 如果uri为空或者uri格式错误
        return BAD_REQUEST;
    }
    request.mUri = std::string(url);    // 将请求对象的uri设置

    parse_state = PARSE_HEADER;     // 解析状态转移到解析头部
    return NO_REQUEST;
}

// 解析请求体中的请求头内容，
// line为请求头起始字符的指针，
// parse_state指代当前解析进度，
// request为需要设置的请求实体。
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_headers(char *line, PARSE_STATE &parse_state, HttpRequest &request) {

    if (*line == '\0') {    // 如果请求头为空
        if (request.mMethod == HttpRequest::GET) {  // 如果是GET方法，此处解析终止，解析器返回GET_REQUEST表示已收到请求
            return GET_REQUEST;
        }
        parse_state = PARSE_BODY;   // 不然就设置为解析请求体的内容
        return NO_REQUEST;
    }

    // FIXME  char key[20]曾被缓冲区溢出, value[100]也被 chrome的user-agent 溢出
    char key[100], value[300];

    // FIXME 需要修改有些value里也包含了':'符号
    sscanf(line, "%[^:]:%[^:]", key, value);


    decltype(HttpRequest::header_map)::iterator it;
    std::string key_s(key);
    std::transform(key_s.begin(), key_s.end(), key_s.begin(), ::toupper);
    std::string value_s(value);
//    if (key_s == std::string("UPGRADE-INSECURE-REQUESTS")) {
//        return NO_REQUEST;
//    }

    if ((it = HttpRequest::header_map.find(trim(key_s))) != (HttpRequest::header_map.end())) {
        request.mHeaders.insert(std::make_pair(it->second, trim(value_s)));
    } else {
        //std::cout << "Header no support: " << key << " : " << value << std::endl;
    }

    return NO_REQUEST;
}

// 解析body
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_body(char *body, HttpRequest &request) {
    request.mContent = body;
    return GET_REQUEST;
}

// http 请求入口
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_content(char *buffer, int &check_index, int &read_index,
                                 HttpRequestParser::PARSE_STATE &parse_state, int &start_line,
                                 HttpRequest &request) {

    LINE_STATE line_state = LINE_OK;
    HTTP_CODE retcode = NO_REQUEST;
    while ((line_state = parse_line(buffer, check_index, read_index)) == LINE_OK) {
        char *temp = buffer + start_line;      // 这一行在buffer中的起始位置
        start_line = check_index;              // 下一行起始位置

        switch (parse_state) {
            case PARSE_REQUESTLINE: {
                retcode = parse_requestline(temp, parse_state, request);
                if (retcode == BAD_REQUEST)
                    return BAD_REQUEST;

                break;
            }

            case PARSE_HEADER: {
                retcode = parse_headers(temp, parse_state, request);
                if (retcode == BAD_REQUEST) {
                    return BAD_REQUEST;
                } else if (retcode == GET_REQUEST) {
                    return GET_REQUEST;
                }
                break;
            }

            case PARSE_BODY: {
                retcode = parse_body(temp, request);
                if (retcode == GET_REQUEST) {
                    return GET_REQUEST;
                }
                return BAD_REQUEST;
            }
            default:
                return INTERNAL_ERROR;
        }
    }
    if (line_state == LINE_MORE) {
        return NO_REQUEST;
    } else {
        return BAD_REQUEST;
    }
}