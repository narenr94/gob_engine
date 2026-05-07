include(GoogleTest)

set(EXEC_NAME characterTests)

set(SRC_ROOT "../../../")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(TEST_SOURCES characterTests.cpp)

add_executable(${EXEC_NAME}
               ${TEST_SOURCES})

target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})

utest_run_add(${EXEC_NAME})