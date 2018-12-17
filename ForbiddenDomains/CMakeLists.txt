cmake_minimum_required(VERSION 3.12)
project(ForbiddenDomains)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(ForbiddenDomains main.cpp)
target_link_libraries(ForbiddenDomains libtest_runner.a)