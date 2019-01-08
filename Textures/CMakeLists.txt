cmake_minimum_required(VERSION 3.13)
project(Textures)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(Textures main.cpp Textures.cpp Textures.h Common.h Solution.cpp)


target_link_libraries(Textures libtest_runner.a)