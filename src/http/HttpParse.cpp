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

// 解析请求体中的请求头单行内容，
// line为请求头单行起始字符的指针，
// parse_state指代当前解析进度，
// request为需要设置的请求实体。
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_headers(char *line, PARSE_STATE &parse_state, HttpRequest &request) {

    if (*line == '\0') {    // 如果该行请求头为空
        if (request.mMethod == HttpRequest::GET) {  // 如果是GET方法，此处解析终止，解析器返回GET_REQUEST表示已收到请求
            return GET_REQUEST;
        }
        parse_state = PARSE_BODY;   // 不然就设置为解析请求体的内容
        return NO_REQUEST;
    }

    // FIXME  char key[20]曾被缓冲区溢出, value[100]也被 chrome的user-agent 溢出
    char key[100], value[300];

    // FIXME 需要修改有些value里也包含了':'符号
    sscanf(line, "%[^:]:%[^:]", key, value);    // 从一行中读出key值和value值


    decltype(HttpRequest::header_map)::iterator it;     // 取header_map的迭代器类型赋给 it
    std::string key_s(key);     // 构造string版本的key
    std::transform(key_s.begin(), key_s.end(), key_s.begin(), ::toupper);   // transform函数为从参数一迭代器到参数二迭代器的左开右闭区间应用参数四指定的操作，并将结果保存在以参数三开始的区间中
                                                                            // transform函数还有二元操作的形式，需要在参数二和三之间插入一个参数，代表第二个参数的取值范围的开头
    std::string value_s(value);     // 构造string版本的value

    if ((it = HttpRequest::header_map.find(trim(key_s))) != (HttpRequest::header_map.end())) {      // 对字符串截断两边的多余字符之后查找这个字段是否存在于header_map中
        request.mHeaders.insert(std::make_pair(it->second, trim(value_s)));     // 如果查的到，则将该头部选项对应的HTTP_HEADER和字段值组成pair插入到request对象的mHeaders中
    } else {    // 不然啥都不做
        //std::cout << "Header no support: " << key << " : " << value << std::endl;
    }

    return NO_REQUEST;  // 该header处理完毕
}

// 解析body
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_body(char *body, HttpRequest &request) {
    request.mContent = body;    // 其实压根没解析只是把body赋值给mContent罢了
    return GET_REQUEST;
}

// http 请求入口
// 解析请求内容
HttpRequestParser::HTTP_CODE HttpRequestParser::parse_content(char *buffer, int &check_index, int &read_index,
                                 HttpRequestParser::PARSE_STATE &parse_state, int &start_line,
                                 HttpRequest &request) {

    LINE_STATE line_state = LINE_OK;
    HTTP_CODE retcode = NO_REQUEST;

    // 开始对整个http request进行解析，buffer是整个request字符串的缓存地址，while循环会将该request一行一行读出来进行解析
    while ((line_state = parse_line(buffer, check_index, read_index)) == LINE_OK) {     // 如果读的出来一行的话
        char *temp = buffer + start_line;      // 该行起始字符的地址，start_line是该行起始字符的索引
        start_line = check_index;              // 索引跳转到下一行

        switch (parse_state) {      // 根据parse_state决定如何解析这一行
            case PARSE_REQUESTLINE: {       // 如果是在解析请求行，调用parse_requestline函数对该行进行解析
                retcode = parse_requestline(temp, parse_state, request);    // 保存返回的状态码
                if (retcode == BAD_REQUEST)     // 如果该请求出错，则终止解析并且返回BAD_REQUEST状态
                    return BAD_REQUEST;

                break;  // 跳出switch
            }

            case PARSE_HEADER: {    // 如果是在解析请求头的某一行，调用parse_headers函数对该行进行解析
                retcode = parse_headers(temp, parse_state, request);    // 保存返回的状态码
                if (retcode == BAD_REQUEST) {
                    return BAD_REQUEST;     // 因为这个函数并不会返回BAD_REQUEST状态，所以这里也不会返回BAD_REQUEST
                } else if (retcode == GET_REQUEST) {    // 如果是GET方法则返回GET_REQUEST，已经生成了request
                    return GET_REQUEST;
                }
                break;  // 跳出switch
            }

            case PARSE_BODY: {      // 如果是在解析body内容，则调用parse_body函数
                retcode = parse_body(temp, request);
                if (retcode == GET_REQUEST) {
                    return GET_REQUEST;     // 解析完成，返回GET_REQUEST
                }
                return BAD_REQUEST;     // 因为这个函数并不会返回BAD_REQUEST状态，所以这里也不会返回BAD_REQUEST
            }
            default:    // 如果有其他的真是见鬼了
                return INTERNAL_ERROR;
        }
    }
    if (line_state == LINE_MORE) {  // 如果request字符串不完整
        return NO_REQUEST;  // 初始化request尚未完成
    } else {    // 如果是LINE_BAD
        return BAD_REQUEST; // 初始化request失败
    }
}