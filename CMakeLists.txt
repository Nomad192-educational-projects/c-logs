cmake_minimum_required(VERSION 3.22)
project(_logs LANGUAGES C VERSION 1.0.0)
set(CMAKE_C_STANDARD 90)
set(CMAKE_BUILD_TYPE Release)

add_library(${PROJECT_NAME} STATIC logs.c logs.h)

add_executable(example example.c)

target_link_libraries(example ${PROJECT_NAME})