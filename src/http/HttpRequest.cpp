//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../../include/HttpRequest.h"

std::ostream &operator<<(std::ostream &os, const HttpRequest &request) {    // 重载输出操作符的实现
    os << "method:" << request.mMethod << std::endl;
    os << "uri:" << request.mUri << std::endl;
    os << "version:" << request.mVersion << std::endl;
    //os << "content:" << request.mContent << std::endl;
    for (auto it = request.mHeaders.begin(); it != request.mHeaders.end(); it++) {
        os << it->first << ":" << it->second << std::endl;
    }
    return os;
}