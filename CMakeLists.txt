cmake_minimum_required(VERSION 3.22)
project(my_logging)

set(CMAKE_C_STANDARD 99)

add_executable(my_logging
        test.c
        logs.c
        logs.h)
