cmake_minimum_required(VERSION 3.12)
project(HashTable)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(HashTable main.cpp)

target_link_libraries(HashTable libtest_runner.a)