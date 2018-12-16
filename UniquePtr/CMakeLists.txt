cmake_minimum_required(VERSION 3.12)
project(UniquePtr)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(UniquePtr main.cpp)
target_link_libraries(UniquePtr libtest_runner.a)