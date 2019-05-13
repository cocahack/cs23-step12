//
// Created by MCC on 2019-05-08.
//

#ifndef STEP12_BARISTA_SYNC_BEVERAGE_H
#define STEP12_BARISTA_SYNC_BEVERAGE_H
#include <string>

class Beverage
{
public:
    int consume_time = 0;
    std::string name = "";
    Beverage(int time, std::string n):consume_time(time), name(n){}
    ~Beverage(){}
};

#endif //STEP12_BARISTA_SYNC_BEVERAGE_H
