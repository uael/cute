cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
project(cute)

cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

option(${PROJECT_NAME}_DEVEL "Build as development environment" ON)
option(COVERAGE "Turn on COVERAGE support" OFF)

if ("${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
    set(CLANG TRUE)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    set(GCC TRUE)
elseif ("${CMAKE_C_COMPILER_ID}" MATCHES "Intel")
    set(ICC TRUE)
elseif (NOT MSVC)
    message(FATAL_ERROR "Unknown compiler")
endif ()

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (GCC)
        set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
    endif ()
else ()
    set(CMAKE_C_STANDARD 99)
endif ()

if (COVERAGE AND NOT MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

set(${PROJECT_NAME}_HEADERS)
set(${PROJECT_NAME}_SOURCES)
set(${PROJECT_NAME}_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(${PROJECT_NAME}_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(${PROJECT_NAME}_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)
set(${PROJECT_NAME}_VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)

if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR})
    file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/*.h)
endif ()
if (EXISTS ${${PROJECT_NAME}_SOURCE_DIR})
    file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_SOURCE_DIR}/*.c)
endif ()

if (EXISTS ${${PROJECT_NAME}_VENDOR_DIR}/CMakeLists.txt)
    add_subdirectory(${${PROJECT_NAME}_VENDOR_DIR})
endif ()
if (EXISTS ${${PROJECT_NAME}_SOURCE_DIR}/CMakeLists.txt)
    add_subdirectory(${${PROJECT_NAME}_SOURCE_DIR})
endif ()

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${${PROJECT_NAME}_HEADERS}")

if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR})
    target_include_directories(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_INCLUDE_DIR})
endif ()
if (EXISTS ${${PROJECT_NAME}_SOURCE_DIR})
    target_include_directories(${PROJECT_NAME} PRIVATE ${${PROJECT_NAME}_SOURCE_DIR})
endif ()

if (MSVC)
    target_compile_options(${PROJECT_NAME}
      PRIVATE /Oy
      PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
    target_compile_options(${PROJECT_NAME}
      PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer
      PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

if (MSVC)
    set(CMAKE_FLAGS
      CMAKE_C_FLAGS CMAKE_CXX_FLAGS
      CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG
      CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE)
    foreach (CMAKE_FLAG ${CMAKE_FLAGS})
        string(REPLACE "/MD" "/MT" ${CMAKE_FLAG} "${${CMAKE_FLAG}}")
        string(REPLACE "/MDd" "/MTd" ${CMAKE_FLAG} "${${CMAKE_FLAG}}")
    endforeach ()
endif ()

if (${PROJECT_NAME}_DEVEL)
    if (EXISTS ${${PROJECT_NAME}_TEST_DIR}/CMakeLists.txt)
        enable_testing()
        add_subdirectory(${${PROJECT_NAME}_TEST_DIR})
    endif ()

    install(TARGETS ${PROJECT_NAME}
      RUNTIME DESTINATION bin
      ARCHIVE DESTINATION lib
      PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
    if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h)
        install(FILES ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h
          DESTINATION include)
    endif ()
else ()
    set(${PROJECT_NAME}_HEADERS ${PROJECT_NAME}_HEADERS PARENT_SCOPE)
    set(${PROJECT_NAME}_SOURCES ${PROJECT_NAME}_SOURCES PARENT_SCOPE)
    set(${PROJECT_NAME}_INCLUDE_DIR ${PROJECT_NAME}_INCLUDE_DIR PARENT_SCOPE)
    set(${PROJECT_NAME}_SOURCE_DIR ${PROJECT_NAME}_SOURCE_DIR PARENT_SCOPE)
    set(${PROJECT_NAME}_TEST_DIR ${PROJECT_NAME}_TEST_DIR PARENT_SCOPE)
    set(${PROJECT_NAME}_VENDOR_DIR ${PROJECT_NAME}_VENDOR_DIR PARENT_SCOPE)
endif ()
