#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>
#include "beverage.h"
#include "barista.h"
#include "log.h"
#include "manager.h"

// 전역 변수
std::vector<int> beverage_time{3, 5, 10};
std::vector<std::string> beverage_name{"아메리카노", "카페라떼", "프라푸치노"};
std::vector<int> orders;


int main()
{
    std::cout << "사용할 수 있는 실제 스레드 개수: " << std::thread::hardware_concurrency() << "\n";
    std::cout << "바리스타를 몇 명 고용하시겠습니까?  ";

    int baristar_size;
    std::cin >> baristar_size;

    std::cout << "바리스타는 총 " << baristar_size << "명입니다.\n";
    std::cout << MENU_PROMPT;
    print_all_menu(beverage_time, beverage_name);
    std::cout << ORDER_PROMPT;

    int order;
    for(int i=0; i < beverage_name.size(); ++i){
        std::cin >> order;
        orders.push_back(order);
    }

    Manager manager{baristar_size};

    for(int i=0; i<orders.size(); ++i){
        while(orders[i]--){
            manager.push_task(Beverage{beverage_time[i], beverage_name[i]});
        }
    }

    while(!manager.task_empty()){
        while(!manager.pool_available()){
            manager.release_thread_if_finished();
        }

        manager.assign_thread();
    }

    while(!manager.all_pool_available()){
        manager.release_thread_if_finished();
    }


    return 0;
}