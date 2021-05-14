//
// Created by 鸢一折纸 on 2021/5/10.
//

#pragma once

//#ifndef WEBSERVER_NONCOPYABLE_H
//#define WEBSERVER_NONCOPYABLE_H

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;

};

//#endif //WEB_SERVER_DEVELOPING_NONCOPYABLE_H
