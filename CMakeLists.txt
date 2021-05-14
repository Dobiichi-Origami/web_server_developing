cmake_minimum_required(VERSION 3.16)
project(web_server_developing)

set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(web_server_developing src/main.cpp include/noncopyable.h src/Util.cpp include/Util.h include/MutexLock.h include/Socket.h src/Socket.cpp include/HttpParse.h include/HttpRequest.h include/HttpResponse.h include/Timer.h src/Timer.cpp include/HttpData.h include/Condition.h include/Epoll.h src/Epoll.cpp include/ThreadPool.h src/ThreadPool.cpp src/http/HttpData.cpp src/http/HttpParse.cpp src/http/HttpRequest.cpp src/http/HttpResponse.cpp include/Server.h src/http/Server.cpp)