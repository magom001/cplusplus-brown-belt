project(tests)
find_package(Catch2 REQUIRED)

set(TESTS date_tests.cpp budget_tests.cpp)

add_executable(tests tests.cpp ${TESTS})
target_link_libraries(tests Catch2::Catch2 personal_budget)