//
// Created by 鸢一折纸 on 2021/5/11.
//

//#ifndef WEB_SERVER_DEVELOPING_SOCKET_H
//#define WEB_SERVER_DEVELOPING_SOCKET_H

#pragma once

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <memory>


class ClientSocket {

public:
    ClientSocket() { fd = -1; };

    void close();

    ~ClientSocket();

    socklen_t mLen;
    sockaddr_in mAddr;
    int fd;
};

void setReusePort(int fd);


class ServerSocket {

public:
    ServerSocket(int port = 8080, const char *ip = nullptr);

    ~ServerSocket();

    void bind();

    void listen();

    void close();

    int accept(ClientSocket &) const;

public:
    sockaddr_in mAddr;
    int listen_fd;
    int epoll_fd;
    int mPort;
    const char *mIp;

};


//#endif //WEB_SERVER_DEVELOPING_SOCKET_H
