//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../../include/Server.h"
#include "../../include/HttpParse.h"
#include "../../include/HttpResponse.h"
#include "../../include/ThreadPool.h"
#include "../../include/HttpData.h"
#include "../../include/Epoll.h"
#include "../../include/Util.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <string>
#include <functional>
#include <sys/epoll.h>
#include <vector>
#include <cstring>


// 404页面
char NOT_FOUND_PAGE[] = "<html>\n"
                        "<head><title>404 Not Found</title></head>\n"
                        "<body bgcolor=\"white\">\n"
                        "<center><h1>404 Not Found</h1></center>\n"
                        "<hr><center>LC WebServer/0.3 (Linux)</center>\n"
                        "</body>\n"
                        "</html>";

// 403页面
char FORBIDDEN_PAGE[] = "<html>\n"
                        "<head><title>403 Forbidden</title></head>\n"
                        "<body bgcolor=\"white\">\n"
                        "<center><h1>403 Forbidden</h1></center>\n"
                        "<hr><center>LC WebServer/0.3 (Linux)</center>\n"
                        "</body>\n"
                        "</html>";

// 默认主页
char INDEX_PAGE[] = "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<head>\n"
                    "    <title>Welcome to LC WebServer!</title>\n"
                    "    <style>\n"
                    "        body {\n"
                    "            width: 35em;\n"
                    "            margin: 0 auto;\n"
                    "            font-family: Tahoma, Verdana, Arial, sans-serif;\n"
                    "        }\n"
                    "    </style>\n"
                    "</head>\n"
                    "<body>\n"
                    "<h1>Welcome to LC WebServer!</h1>\n"
                    "<p>If you see this page, the lc webserver is successfully installed and\n"
                    "    working. </p>\n"
                    "\n"
                    "<p>For online documentation and support please refer to\n"
                    "    <a href=\"https://github.com/MarvinLe/WebServer\">LC WebServer</a>.<br/>\n"
                    "\n"
                    "<p><em>Thank you for using LC WebServer.</em></p>\n"
                    "</body>\n"
                    "</html>";

// 测试页面
char TEST[] = "HELLO WORLD";

// 网页根目录地址
extern std::string basePath;


// 服务器运行
// 设置线程池中执行任务的线程数
// 与任务队列的最大大小
void HttpServer::run(int thread_num, int max_queque_size) {
    ThreadPool threadPool(thread_num, max_queque_size);

    int epoll_fd = Epoll::init(1024);

    std::shared_ptr<HttpData> httpData(new HttpData());
    httpData->epoll_fd = epoll_fd;
    serverSocket.epoll_fd = epoll_fd;

    __uint32_t event = (EPOLLIN | EPOLLET); // 电平触发模式下监听输入事件
    Epoll::addFd(epoll_fd, serverSocket.listen_fd, event, httpData);    // 添加服务器监听端口的监听事件

    while (true) {  // 从EPOLL中轮询获取工作

        std::vector<std::shared_ptr<HttpData>> events = Epoll::poll(serverSocket, 1024, -1);
        // FIXME 将事件传递给 线程池
        for (auto& req : events) {
            threadPool.append(req, std::bind(&HttpServer::do_request, this, std::placeholders::_1));
        }
        // 处理定时器超时事件
        Epoll::timerManager.handle_expired_event();
    }
}


void HttpServer::do_request(std::shared_ptr<void> arg) {
    std::shared_ptr<HttpData> sharedHttpData = std::static_pointer_cast<HttpData>(arg);

    char buffer[BUFFERSIZE];

    bzero(buffer, BUFFERSIZE); // 初始化缓冲区
    int check_index = 0, read_index = 0, start_line = 0;
    ssize_t recv_data;  // ssize_t 是个 long int
    HttpRequestParser::PARSE_STATE  parse_state = HttpRequestParser::PARSE_REQUESTLINE;

    while (true) {

        // FIXME 这里也是同样的，由于是非阻塞IO，所以返回-1 也不一定是错误，还需判断error
        recv_data = recv(sharedHttpData->clientSocket_->fd, buffer + read_index, BUFFERSIZE - read_index, 0);
        if (recv_data == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                return;  // FIXME 请求不完整该怎么办，继续加定时器吗？还是直接关闭
            }
            std::cout << "reading faild" << std::endl;
            return;
        }
        // todo 返回值为 0对端关闭, 这边也应该关闭定时器

        if (recv_data == 0) {
            std::cout << "connection closed by peer" << std::endl;
            break;
        }
        read_index += recv_data;

        HttpRequestParser::HTTP_CODE  retcode = HttpRequestParser::parse_content(
                buffer, check_index, read_index, parse_state, start_line, *sharedHttpData->request_);

        if (retcode == HttpRequestParser::NO_REQUEST) {
            continue;
        }


        if (retcode == HttpRequestParser::GET_REQUEST) {
            // FIXME 检查 keep_alive选项
            auto it = sharedHttpData->request_->mHeaders.find(HttpRequest::Connection);
            if (it != sharedHttpData->request_->mHeaders.end()) {
                if (it->second == "keep-alive") {
                    sharedHttpData->response_->setKeepAlive(true);
                    // timeout=20s
                    sharedHttpData->response_->addHeader("Keep-Alive", std::string("timeout=20"));
                } else {
                    sharedHttpData->response_->setKeepAlive(false);
                }
            }
            header(sharedHttpData);
            getMime(sharedHttpData);

            FileState fileState = static_file(sharedHttpData, basePath.c_str());
            send(sharedHttpData, fileState);
            // 如果是keep_alive else sharedHttpData将会自动析构释放clientSocket，从而关闭资源
            if (sharedHttpData->response_->isKeepAlive()) {
                //FIXME std::cout << "再次添加定时器  keep_alive: " << sharedHttpData->clientSocket_->fd << std::endl;

                // 设置oneshot并且触发后，必须重新设定该socket对应fd的监听事件
                Epoll::modFd(sharedHttpData->epoll_fd, sharedHttpData->clientSocket_->fd, Epoll::DEFAULT_EVENTS, sharedHttpData);
                Epoll::timerManager.addTimer(sharedHttpData, TimerManager::DEFAULT_TIME_OUT);
            }

        } else {
            // todo Bad Request 应该关闭定时器,(其实定时器已经关闭,在每接到一个新的数据时)
            std::cout << "Bad Request" << std::endl;
        }
    }
}

void HttpServer::header(std::shared_ptr<HttpData> httpData) {
    if (httpData->request_->mVersion == HttpRequest::HTTP_11) {
        httpData->response_->setMVersion(HttpRequest::HTTP_11);
    } else {
        httpData->response_->setMVersion(HttpRequest::HTTP_10);
    }
    httpData->response_->addHeader("Server", "LC WebServer");
}


// 获取Mime 同时设置path到response
void HttpServer::getMime(std::shared_ptr<HttpData> httpData) {
    std::string filepath = httpData->request_->mUri;
    std::string mime;
    int pos;
//    std::cout << "uri: " << filepath << std::endl;
    // FIXME 直接将参数丢掉了，后续可以开发
    if ((pos = filepath.rfind('?')) != std::string::npos) {
        filepath.erase(filepath.rfind('?'));
    }

    if (filepath.rfind('.') != std::string::npos){
        mime = filepath.substr(filepath.rfind('.'));
    }
    decltype(Mime_map)::iterator it;

    if ((it = Mime_map.find(mime)) != Mime_map.end()) {
        httpData->response_->setMMime(it->second);
    } else {
        httpData->response_->setMMime(Mime_map.find("default")->second);
    }
    httpData->response_->setMFilePath(filepath);
}

HttpServer::FileState HttpServer::static_file(std::shared_ptr<HttpData> httpData, const char *basepath) {
    struct stat file_stat;
    char file[strlen(basepath) + strlen(httpData->response_->getMFilePath().c_str())+1];
    strcpy(file, basepath);
    strcat(file, httpData->response_->getMFilePath().c_str());

    // 文件不存在
    if (httpData->response_->getMFilePath() == "/" || stat(file, &file_stat) < 0) {
        // FIXME 设置Mime 为 html
        httpData->response_->setMMime(MimeType("text/html"));
        if (httpData->response_->getMFilePath() == "/") {
            httpData->response_->setMStatusCode(HttpResponse::k200Ok);
            httpData->response_->setMStatusMsg("OK");
        } else {
            httpData->response_->setMStatusCode(HttpResponse::k404NotFound);
            httpData->response_->setMStatusMsg("Not Found");
        }
        // 废弃，404就不需要设置filepath
        //httpData->response_->setFilePath(std::string(basepath)+"/404.html");
        //std::cout << "File Not Found: " <<   file << std::endl;
        return FILE_NOT_FOUND;
    }
    // 不是普通文件或无访问权限
    if(!S_ISREG(file_stat.st_mode)){
        // FIXME 设置Mime 为 html
        httpData->response_->setMMime(MimeType("text/html"));
        httpData->response_->setMStatusCode(HttpResponse::k403Forbidden);
        httpData->response_->setMStatusMsg("ForBidden");
        // 废弃， 403就不需要设置filepath
        //httpData->response_->setFilePath(std::string(basepath)+"/403.html");
        std::cout << "not normal file" << std::endl;
        return FILE_FORBIDDEN;
    }

    httpData->response_->setMStatusCode(HttpResponse::k200Ok);
    httpData->response_->setMStatusMsg("OK");
    httpData->response_->setMFilePath(file);
//    std::cout << "文件存在 - ok" << std::endl;
    return FILE_OK;
}

void HttpServer::send(std::shared_ptr<HttpData> httpData, FileState fileState) {
    char header[BUFFERSIZE];
    bzero(header, '\0');
    const char *internal_error = "Internal Error";
    struct stat file_stat;
    httpData->response_->appendBuffer(header);
    // 404
    if (fileState == FILE_NOT_FOUND) {

        // 如果是 '/'开头就发送默认页
        if (httpData->response_->getMFilePath() == std::string("/")) {
            // 现在使用测试页面
            sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(INDEX_PAGE));
            sprintf(header, "%s%s", header, INDEX_PAGE);
        } else {
            sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(NOT_FOUND_PAGE));
            sprintf(header, "%s%s", header, NOT_FOUND_PAGE);
        }
        ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
        return;
    }

    if (fileState == FILE_FORBIDDEN) {
        sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(FORBIDDEN_PAGE));
        sprintf(header, "%s%s", header, FORBIDDEN_PAGE);
        ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
        return;
    }
    // 获取文件状态
    if (stat(httpData->response_->getMFilePath().c_str(), &file_stat) < 0) {
        sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
        sprintf(header, "%s%s", header, internal_error);
        ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
        return;
    }

    int filefd = ::open(httpData->response_->getMFilePath().c_str(), O_RDONLY);
    // 内部错误
    if (filefd < 0) {
        std::cout << "打开文件失败" << std::endl;
        sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
        sprintf(header, "%s%s", header, internal_error);
        ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
        close(filefd);
        return;
    }

    sprintf(header,"%sContent-length: %d\r\n\r\n", header, file_stat.st_size);
    ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
    void *mapbuf = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, filefd, 0);
    ::send(httpData->clientSocket_->fd, mapbuf, file_stat.st_size, 0);
    munmap(mapbuf, file_stat.st_size);
    close(filefd);
    return;
    err:
    sprintf(header, "%sContent-length: %d\r\n\r\n", header, strlen(internal_error));
    sprintf(header, "%s%s", header, internal_error);
    ::send(httpData->clientSocket_->fd, header, strlen(header), 0);
    return;
}