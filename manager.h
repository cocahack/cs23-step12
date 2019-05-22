//
// Created by MCC on 2019-05-08.
//

#ifndef STEP12_BARISTA_SYNC_MANAGER_H
#define STEP12_BARISTA_SYNC_MANAGER_H

#include <thread>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include <queue>
#include <iostream>
#include "barista.h"
#include "beverage.h"

class Manager
{
private:
    int baristar_size;
    std::vector<std::pair<std::thread, int>> thread_container;
    std::queue<int> available_barista;
    std::queue<Beverage> task_queue;

    int select_barista()
    {
        auto ret = available_barista.front();
        available_barista.pop();
        return ret;
    }
public:
    Manager(int size):baristar_size(size)
    {
        for(int i=0; i<size; ++i){
            available_barista.push(i+1);
        }
    }

    void assign_thread()
    {
        if(available_barista.empty()) throw "모든 바리스타가 커피를 만들고 있습니다..";
        if(task_queue.empty()) throw "작업이 없습니다.";

        auto task = task_queue.front();
        task_queue.pop();

        int next_barista = select_barista();
        thread_container.push_back(
                std::make_pair(
                        std::move(std::thread{&Barista::make_beverage, Barista{next_barista}, task}), next_barista)
        );
    }

    void push_task(Beverage b)
    {
        task_queue.push(b);
    }

    int task_empty()
    {
        return task_queue.empty();
    }

    bool pool_available()
    {
        return !available_barista.empty();
    }

    bool all_pool_available()
    {
        return available_barista.size() == baristar_size;
    }

    void release_thread_if_finished()
    {
        auto iter = thread_container.begin();
        while (iter != thread_container.end())
            if (iter->first.joinable()) {
                iter->first.join();

                available_barista.push(iter->second);
                thread_container.erase(iter);
                break;
            }
        ++iter;
    }

    ~Manager()
    {
        while(thread_container.size()) {
            release_thread_if_finished();
        }
    }
};

#endif //STEP12_BARISTA_SYNC_MANAGER_H
