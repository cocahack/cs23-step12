cmake_minimum_required(VERSION 3.14)
project(step12_barista_sync)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(step12_barista_sync main.cpp log.h barista.h beverage.h manager.h print_thread.h print_thread.h)