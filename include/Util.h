//
// Created by 鸢一折纸 on 2021/5/10.
//

#pragma once

//#ifndef WEB_SERVER_DEVELOPING_UTIL_H
//#define WEB_SERVER_DEVELOPING_UTIL_H

#include <string>

using std::string;


string &ltrim(string &);

string &rtrim(string &);

string &trim(string &);

int setNonblocking(int fd);

void handle_for_sigpipe();

int check_base_path(char *basePath);


//#endif //WEB_SERVER_DEVELOPING_UTIL_H
