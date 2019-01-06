cmake_minimum_required(VERSION 3.13)
project(Polynomial)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Polynomial main.cpp profile.h)


target_link_libraries(Polynomial libtest_runner.a)