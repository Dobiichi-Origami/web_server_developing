//
// Created by 鸢一折纸 on 2021/5/10.
//

#pragma once

//#ifndef WEBSERVER_NONCOPYABLE_H
//#define WEBSERVER_NONCOPYABLE_H

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;   // 禁用拷贝构造函数
    noncopyable& operator=(const noncopyable&) = delete;    // 禁用赋值函数

protected:
    noncopyable() = default;
    ~noncopyable() = default;

};

//#endif //WEB_SERVER_DEVELOPING_NONCOPYABLE_H
