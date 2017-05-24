file(GLOB ctest_SOURCES ${ctest_SOURCES} ${CMAKE_CURRENT_LIST_DIR}/*.c)

foreach(ctest_src ${ctest_SOURCES})
    get_filename_component(ctest_name ${ctest_src} NAME_WE)
    add_executable(test_${ctest_name} ${ctest_src})
    add_dependencies(test_${ctest_name} ${PROJECT_NAME})
    target_link_libraries(test_${ctest_name} ${PROJECT_NAME})
    add_test(${ctest_name} test_${ctest_name})
endforeach()
