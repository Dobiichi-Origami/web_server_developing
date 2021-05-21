//
// Created by 鸢一折纸 on 2021/5/12.
//

//#ifndef WEB_SERVER_DEVELOPING_SERVER_H
//#define WEB_SERVER_DEVELOPING_SERVER_H

#pragma once

#include "Socket.h"
#include "HttpParse.h"
#include "HttpResponse.h"
#include "HttpData.h"
#include <memory>

#define BUFFERSIZE 2048

class HttpServer {
public:
    enum FileState {    // 文件状态枚举集合
        FILE_OK,
        FILE_NOT_FOUND,
        FILE_FORBIDDEN
    };

public:

    // Http服务器构造函数，默认端口80，监听所有端口
    explicit HttpServer(int port = 80, const char *ip = nullptr) : serverSocket(port, ip) {
        serverSocket.bind();    // 绑定具体的地址
        serverSocket.listen();  // 开始监听
    }

    void run(int, int max_queue_size = 10000);

    void do_request(std::shared_ptr<void> arg);

private:
    void header(std::shared_ptr<HttpData>);

    FileState static_file(std::shared_ptr<HttpData>, const char *);

    void send(std::shared_ptr<HttpData>, FileState);

    void getMime(std::shared_ptr<HttpData>);
    void hanleIndex();

    ServerSocket serverSocket;
};

//#endif //WEB_SERVER_DEVELOPING_SERVER_H
