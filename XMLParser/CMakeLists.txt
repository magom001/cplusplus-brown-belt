cmake_minimum_required(VERSION 3.13)
project(XMLParser)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(XMLParser main.cpp xml.cpp xml.h)

target_link_libraries(XMLParser libtest_runner.a)