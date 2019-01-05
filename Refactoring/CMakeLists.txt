cmake_minimum_required(VERSION 3.13)
project(Refactoring)

set(CMAKE_CXX_STANDARD 17)


link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Refactoring main.cpp json.cpp json.h xml.cpp xml.h)

target_link_libraries(Refactoring libtest_runner.a)