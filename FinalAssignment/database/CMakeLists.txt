project(database)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        stop.h
        bus.h
        database.h
        iterator_range.h
        parse.h
        program_runner.h
        )

set(SOURCE_FILES
        stop.cpp
        bus.cpp
        database.cpp
        parse.cpp
        )

add_library(database STATIC ${SOURCE_FILES} ${HEADER_FILES})