project(database)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        database.h
        bus.h
        parse.h
        global.h
        stop.h
        program_runner.h
        )

set(SOURCE_FILES
        database.cpp
        bus.cpp
        parse.cpp
        stop.cpp
        )

add_library(database STATIC ${SOURCE_FILES} ${HEADER_FILES})