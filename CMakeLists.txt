cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(cute)

option(COVERAGE "Turn on COVERAGE support" OFF)

if(COVERAGE AND NOT MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif()

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    endif()
else()
    set(CMAKE_C_STANDARD 99)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3")
else()
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3 -DDEBUG")
    else()
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
    endif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Werror -fomit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-missing-field-initializers -Wno-unused-parameter -Wno-unused-function")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -Wno-unused-value -Wno-unused-result -Wno-missing-braces")
endif()

if(MSVC)
    set(CMAKE_FLAGS
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
    )
    foreach(CMAKE_FLAG ${CMAKE_FLAGS})
        string(REPLACE "/MD" "/MT" ${CMAKE_FLAG} "${${CMAKE_FLAG}}")
        string(REPLACE "/MDd" "/MTd" ${CMAKE_FLAG} "${${CMAKE_FLAG}}")
    endforeach()
endif()

set(cute_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(cute_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(cute_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB_RECURSE cute_HEADERS ${cute_HEADERS} ${cute_INCLUDE_DIR}/*.h)
file(GLOB_RECURSE cute_SOURCES ${cute_SOURCES} ${cute_SOURCE_DIR}/*.c)

add_library(${PROJECT_NAME} STATIC ${cute_SOURCES} ${cute_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${cute_HEADERS}")
target_include_directories(${PROJECT_NAME} PUBLIC ${cute_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${cute_SOURCE_DIR})

if(EXISTS ${cute_TEST_DIR})
    enable_testing()
    add_subdirectory(${cute_TEST_DIR})
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
