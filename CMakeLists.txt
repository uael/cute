cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cute)

option(COVERAGE "Turn on COVERAGE support" OFF)

if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    endif()
else()
    set(CMAKE_C_STANDARD 99)
endif()

if(COVERAGE AND NOT MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif()

set(cute_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(cute_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(cute_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB_RECURSE cute_HEADERS ${cute_HEADERS} ${cute_INCLUDE_DIR}/*.h)
file(GLOB_RECURSE cute_SOURCES ${cute_SOURCES} ${cute_SOURCE_DIR}/*.c)

add_library(${PROJECT_NAME} STATIC ${cute_SOURCES} ${cute_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${cute_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${cute_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${cute_HEADERS}")

target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
if(NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wextra)
endif()
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG")
    if(NOT MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE -O0 -g3)
    endif()
elseif(NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
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

if(EXISTS ${cute_TEST_DIR})
    enable_testing()
    add_subdirectory(${cute_TEST_DIR})
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
