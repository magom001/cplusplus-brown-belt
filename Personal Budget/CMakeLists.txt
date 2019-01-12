cmake_minimum_required(VERSION 3.13)
project(Main)

set(CMAKE_CXX_STANDARD 17)

include_directories(personal_budget)

add_subdirectory(tests)
add_subdirectory(personal_budget)

add_executable(Main main.cpp)

target_link_libraries(Main personal_budget)