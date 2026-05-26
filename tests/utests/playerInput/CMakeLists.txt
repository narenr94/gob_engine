include(GoogleTest)

set(SRC_ROOT "../../../")
set(FAKE_ROOT "../fakes/")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(ACT_SRCS ${SRC_ROOT}/src/playerInput.cpp)

set(FAKE_SRCS ${FAKE_ROOT}/fakeLog.cpp)

# PlayerInput Tests
set(EXEC_NAME playerInputTests)

set(TEST_SOURCES playerInputTests.cpp)

add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS}
               ${FAKE_SRCS})

target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})

utest_run_add(${EXEC_NAME})
