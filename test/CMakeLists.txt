cmake_minimum_required(VERSION 3.8)
# Testing
##################################################
set(TESTS smpl_test.c)
set(TEST_MAIN tests)
set(TEST_RUNNER_PARAMS "")

add_executable(${TEST_MAIN} ${TESTS})

if(NOT MSVC)
    target_link_libraries(${TEST_MAIN} PRIVATE m)
endif()

target_link_libraries(${TEST_MAIN} PRIVATE sparse)
target_include_directories(${TEST_MAIN} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)

set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


#add_test(
#    NAME sparse.${TEST_MAIN}
#    COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS}
#    )
