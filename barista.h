//
// Created by MCC on 2019-05-08.
//

#ifndef STEP12_BARISTA_SYNC_BARISTA_H
#define STEP12_BARISTA_SYNC_BARISTA_H

#include "print_thread.h"
#include "beverage.h"
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

class Barista
{
private:
    int id;
public:
    Barista(int id_):id(id_){}
    void make_beverage(Beverage b)
    {
        auto begin_time = system_clock::to_time_t(system_clock::now());
        std::this_thread::sleep_for(std::chrono::milliseconds(b.consume_time * 1000));
        auto end_time = system_clock::to_time_t(system_clock::now());
        print_thread{} << "바리스타"
                       << id
                       << "-"
                       << b.name
                       << "\n시작 시각: "
                       << std::ctime(&begin_time)
                       << "종료 시각: "
                       << std::ctime(&end_time)
                       << "1초 휴식 합니다.\n"
                       << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    int get_id()
    {
        return id;
    }
};

#endif //STEP12_BARISTA_SYNC_BARISTA_H
