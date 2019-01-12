project(personal_budget)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        budget.h
        date.h
        )

set(SOURCE_FILES
        budget.cpp
        date.cpp
        )

add_library(personal_budget STATIC ${SOURCE_FILES} ${HEADER_FILES})