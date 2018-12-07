cmake_minimum_required(VERSION 3.12)
project(DatabaseIndex)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(DatabaseIndex main.cpp Database.h)
target_link_libraries(DatabaseIndex libtest_runner.a)