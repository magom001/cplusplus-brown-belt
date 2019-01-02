project(database)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES
        database.h
        bus.h
        parse.h
        global.h
        stop.h
        program_runner.h
        json.h
        response.h
        graph.h
        router.h
        json_runner.h)

set(SOURCE_FILES
        database.cpp
        bus.cpp
        parse.cpp
        stop.cpp
        json.cpp
        response.cpp)

add_library(database STATIC ${SOURCE_FILES} ${HEADER_FILES})