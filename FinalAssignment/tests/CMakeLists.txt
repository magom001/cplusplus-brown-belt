project(tests)
find_package(Catch2 REQUIRED)

set(DEPENDENCIES
        profiler.h
        )

set(TESTS
        bus_tests.cpp
        coordinates_tests.cpp
        database_tests.cpp
        program_runner_tests.cpp
        stop_tests.cpp distance_tests.cpp
        json_tests.cpp json_runner_tests.cpp dwg_tests.cpp json_file_tests.cpp)

add_executable(tests tests.cpp ${TESTS} ${DEPENDENCIES})
target_link_libraries(tests Catch2::Catch2 database)