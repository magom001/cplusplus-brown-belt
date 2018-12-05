cmake_minimum_required(VERSION 3.12)
project(PersonHashFunction)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(PersonHashFunction main.cpp)
target_link_libraries(PersonHashFunction libtest_runner.a)