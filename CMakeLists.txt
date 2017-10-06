cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(cute C)

set(cute_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(cute_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(cute_HDR ${cute_INC_DIR}/cute.h)

add_library(cute INTERFACE)
target_include_directories(cute INTERFACE ${cute_INC_DIR})

get_directory_property(cute_PARENT PARENT_DIRECTORY)
if (NOT cute_PARENT)
  set(cute_DEVEL TRUE)
elseif (NOT cute_DEVEL)
  set(cute_DEVEL FALSE)
endif ()
if (cute_DEVEL AND EXISTS ${cute_TEST_DIR})
  if (NOT cute_PARENT)
    enable_testing()
  endif ()

  file(GLOB cute_TEST_SRCS ${cute_TEST_SRCS} ${cute_TEST_DIR}/*.c)
  foreach (cute_TEST_SRC ${cute_TEST_SRCS})
    get_filename_component(cute_TEST_NAME ${cute_TEST_SRC} NAME_WE)
    add_executable(test_cute_${cute_TEST_NAME} ${cute_TEST_SRC})
    add_dependencies(test_cute_${cute_TEST_NAME} cute)
    target_link_libraries(test_cute_${cute_TEST_NAME} cute)
    add_test(${cute_TEST_NAME} test_cute_${cute_TEST_NAME})
  endforeach ()
endif ()

install(FILES ${cute_HDR}
  DESTINATION include)
