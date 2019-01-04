cmake_minimum_required(VERSION 3.13)
project(Polymorphism)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Polymorphism main.cpp geo2d.cpp geo2d.h game_object.h)
target_link_libraries(Polymorphism libtest_runner.a)