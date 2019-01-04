cmake_minimum_required(VERSION 3.13)
project(CommentsServer)

set(CMAKE_CXX_STANDARD 17)
link_directories(../test-runner)
include_directories(../test-runner)

add_executable(CommentsServer main.cpp)
target_link_libraries(CommentsServer libtest_runner.a)