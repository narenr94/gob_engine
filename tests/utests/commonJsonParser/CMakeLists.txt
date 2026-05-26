include(GoogleTest)

set(SRC_ROOT "../../../")
set(FAKE_ROOT "../fakes/")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(ACT_SRCS ${SRC_ROOT}/src/commonJsonParser.cpp
             ${SRC_ROOT}/src/utilities.cpp)

set(FAKE_SRCS ${FAKE_ROOT}/fakeDefines.cpp
               ${FAKE_ROOT}/fakeRaceData.cpp
               ${FAKE_ROOT}/fakeGameData.cpp
               ${FAKE_ROOT}/fakePlayerInput.cpp
               ${FAKE_ROOT}/fakeRandomize.cpp)

# commonJsonParser Tests
set(EXEC_NAME commonJsonParserTests)

set(TEST_SOURCES commonJsonParserTests.cpp)

add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS}
               ${FAKE_SRCS})

target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})

utest_run_add(${EXEC_NAME})
