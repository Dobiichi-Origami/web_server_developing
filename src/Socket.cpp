//
// Created by 鸢一折纸 on 2021/5/11.
//

#include "../include/Socket.h"
#include "../include/Util.h"
#include <cstring>
#include <cstdio>

void setReusePort(int fd) {     //设置这个端口为可立即重新使用（剥夺原有端口的TIME_WAIT()）
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));  //为文件描述符所代表的套接字在第二个参数指定的层级上，设置某个属性的属性值并指定其长度
}

ServerSocket::ServerSocket(int port, const char *ip) : mPort(port), mIp(ip) {   //用指定的端口号 port 和监听的目的地址字符串 ip 来初始化服务器套接字
    bzero(&mAddr, sizeof(mAddr));   //清零这块内存空间
    mAddr.sin_family = AF_INET;     //将地址结构体的地址类型设置为 IPv4
    mAddr.sin_port = htons(port);   //把端口号从大端序的int转换为网络序（小端序）的uint16_t
    if (ip != nullptr) {    //如果指定了监听的 IP 地址
        ::inet_pton(AF_INET, ip, &mAddr.sin_addr);  //根据指定的地址类型，将地址结构体中的 IP 地址结构体内容初始化为指定地址，从字符串转为uint32_t
    } else {
        mAddr.sin_addr.s_addr = htonl(INADDR_ANY);      //不然就全部监听。htonl：将参数值的字节表示转化为网络序（小端序）的u32int_t
    }
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);    //打开一个 IPv4类型的 TCP/IP 链接，由于协议参数为0，系统自行选择一个协议，返回一个文件描述符代表所监听的套接字
    if (listen_fd == -1) {      //如果创建失败
        std::cout << "Creat socket error in file <" << __FILE__ << "> "<< "at" << __LINE__ << std::endl;    //输出当前出错的源文件名字以及行号
        exit(0);
    }
    setReusePort(listen_fd);    //回收这个文件描述符先前可能代表的链接
    setNonblocking(listen_fd);  //将这个文件描述符指定的套接字设置为非阻塞状态以让客户端可以向其中写入数据
}

void ServerSocket::bind() {     //把构造函数中初始化的mAddr与监听套接字绑定在一起
    int ret = ::bind(listen_fd, (struct sockaddr*) &mAddr, sizeof(mAddr));  //绑定操作
    if (ret == -1) {    //如果出错
        std::cout << "bind error in file <" << __FILE__ << "> " << "at " << __LINE__ << std::endl;
        exit(0);
    }
}

void ServerSocket::listen() {   //开始监听套接字的内容，至多1024个请求会被缓存，多余的直接drop put。此时还没开始建立链接，只是从主动端口变为了被动端口
    int ret = ::listen(listen_fd, 1024);
    if (ret == -1) {    //如果出错
        std::cout << "listen error in file <" << __FILE__ << "> " << "at " << __LINE__ << std::cout;
        exit(0);
    }
}

int ServerSocket::accept(ClientSocket &clientSocket) const {    //阻塞程序执行，将队列中的链接请求进行处理，建立连接
    int clientfd = ::accept(listen_fd, NULL, NULL);     //返回一个用于和客户端通信的新套接字，其中客户端的地址信息会被保存在长度为addrlen的sockaddr结构体中，此处留空

    if (clientfd < 0) {     //如果链接建立失败
        if ((errno == EWOULDBLOCK) || (errno == EAGAIN))    //忽视EAGAIN和EWOULDBLOCK，这两个error表示资源暂不可用，可稍后重新再试
            return clientfd;    //当系统资源不可用或者在非阻塞对象中执行阻塞操作可能就会触发这两种错误
        std::cout << "accept error in file <" << __FILE__ << "> " << "at " << __LINE__ << std::endl;
        std::cout << "clientfd: " << clientfd << std::endl;
        perror("accept error");
    }
    clientSocket.fd = clientfd;
    return clientfd;
}

void ServerSocket::close() {    //关闭socket并且将listen_fd置-1
    if (listen_fd >= 0) {
        ::close(listen_fd);
        listen_fd = -1;
    }
}

ServerSocket::~ServerSocket() {     //析构
    close();
}

void ClientSocket::close() {    //同上
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

ClientSocket::~ClientSocket() {
    close();
}