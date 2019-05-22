//
// Created by MCC on 2019-05-08.
//

#ifndef STEP12_BARISTA_SYNC_MANAGER_H
#define STEP12_BARISTA_SYNC_MANAGER_H

#include <thread>
#include <vector>
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
    int assigned_baristar; // 업무중인 바리스타
    std::vector<std::pair<std::thread, Barista>> thread_container;
    std::vector<bool> assigned;
    std::queue<Beverage> task_queue;

    int generate_id()
    {
        int id;
        for(int i=0; i<assigned.size(); ++i){
            if(!assigned[i]){
                assigned[i] = true;
                return i;
            }
        }
        return -1;
    }
public:
    Manager(int size):baristar_size(size),
                           assigned_baristar(0),
                           assigned(std::vector<bool>(size, false))
                           {}

    void assign_thread()
    {
        if(assigned_baristar == baristar_size) throw "모든 바리스타가 커피를 만들고 있습니다..";
        if(task_queue.empty()) throw "작업이 없습니다.";

        auto task = task_queue.front();
        task_queue.pop();

        int id = generate_id();
        Barista barista{id};
        thread_container.push_back(
                std::make_pair(
                        std::move(std::thread{&Barista::make_beverage, barista, task})
                        , barista)
        );
        assigned_baristar++;
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
        return assigned_baristar < baristar_size;
    }

    bool all_pool_available()
    {
        return assigned_baristar == 0;
    }

    void release_thread_if_finished()
    {
        for(auto iter = thread_container.begin();
            iter < thread_container.end() ;
            ++iter){

            if(iter->first.joinable()){
                iter->first.join();

                assigned[iter->second.get_id()] = false;
                thread_container.erase(iter);
                assigned_baristar--;
            }

        }
    }

    ~Manager()
    {
        release_thread_if_finished();
    }
};

#endif //STEP12_BARISTA_SYNC_MANAGER_H
