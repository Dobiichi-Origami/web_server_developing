//
// Created by 鸢一折纸 on 2021/5/12.
//

#include "../../include/HttpData.h"


void HttpData::closeTimer() {   // 测试push
    if (timer_.lock()) {
        std::shared_ptr<TimerNode> tempTimer(timer_.lock());
        tempTimer -> deleted();
        timer_.reset();
    }
}

void HttpData::setTimer(std::shared_ptr<TimerNode> timer) {
    timer_ = timer;
}