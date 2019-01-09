cmake_minimum_required(VERSION 3.13)
project(RAII_Booking)

set(CMAKE_CXX_STANDARD 17)

link_directories(../test-runner)
include_directories(../test-runner)

add_executable(RAII_Booking main.cpp old_booking_providers.h old_trip_manager.h new_booking_providers.h new_trip_manager.h booking.h)

target_link_libraries(RAII_Booking libtest_runner.a)