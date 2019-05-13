//
// Created by MCC on 2019-05-08.
//

#ifndef STEP12_BARISTA_SYNC_PRINT_THREAD_H
#define STEP12_BARISTA_SYNC_PRINT_THREAD_H

#include <iostream>
#include <sstream>
#include <mutex>
#include <string>

class print_thread : public std::ostringstream
{
private:
    static std::mutex mutex_print;
public:
    print_thread() = default;

    ~print_thread()
    {
        std::lock_guard<std::mutex> guard(mutex_print);
        std::cout << this->str();
    }
};

std::mutex print_thread::mutex_print{};
#endif //STEP12_BARISTA_SYNC_PRINT_THREAD_H
