cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)
project(cute)

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    endif()
else()
    set(CMAKE_C_STANDARD 99)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR})

enable_testing()
add_subdirectory(test)

install(FILES ${PROJECT_NAME}.h
    DESTINATION include
)
