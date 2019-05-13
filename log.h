//
// Created by MCC on 2019-05-07.
//

#ifndef STEP12_BARISTA_SYNC_LOG_H
#define STEP12_BARISTA_SYNC_LOG_H

#include <string>
#include <vector>
#include <iostream>
#include "beverage.h"

const std::string MENU_PROMPT = "메뉴 = ";
const std::string ORDER_PROMPT = "차례대로 주문할 음료의 개수를 입력하세요. 예) 1 2 2\n";

void print_all_menu(const std::vector<int>& time, const std::vector<std::string> name)
{
    for(int i=0; i<time.size(); ++i){
        std::cout << i+1 << "." << name[i] << "(" << time[i] << "s)    ";
    }
    std::cout << "\n";
}

#endif //STEP12_BARISTA_SYNC_LOG_H
