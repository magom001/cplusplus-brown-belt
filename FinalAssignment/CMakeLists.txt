cmake_minimum_required(VERSION 3.12)
project(FinalAssignment)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(FinalAssignment ${SOURCE_FILES})

include_directories(database)

add_subdirectory(database)
add_subdirectory(tests)

target_link_libraries(FinalAssignment database)