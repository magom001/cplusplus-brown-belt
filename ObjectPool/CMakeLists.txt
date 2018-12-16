cmake_minimum_required(VERSION 3.12)
project(ObjectPool)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(ObjectPool main.cpp)
target_link_libraries(ObjectPool libtest_runner.a)