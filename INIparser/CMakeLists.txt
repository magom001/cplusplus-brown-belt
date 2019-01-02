cmake_minimum_required(VERSION 3.13)
project(INIparser)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(INIparser main.cpp ini.cpp ini.h)
target_link_libraries(INIparser libtest_runner.a)