include(GoogleTest)

set(SRC_ROOT "../../../")
set(FAKE_ROOT "../fakes/")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(ACT_SRCS ${SRC_ROOT}/src/gameData.cpp
             ${SRC_ROOT}/src/log.cpp
             ${SRC_ROOT}/src/commonJsonParser.cpp
             ${SRC_ROOT}/src/utilities.cpp
             ${SRC_ROOT}/src/defines.cpp)

set(FAKE_SRCS ${FAKE_ROOT}/fakeCharacter.cpp
              ${FAKE_ROOT}/fakePlayerInput.cpp
              ${FAKE_ROOT}/fakeRandomize.cpp
              ${FAKE_ROOT}/fakeRace.cpp)

# Base Character Tests
set(EXEC_NAME gameDataTests)

set(TEST_SOURCES gameDataTests.cpp)

add_definitions(-DTEST_PRINTS)

add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS}
               ${FAKE_SRCS})

target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})

utest_run_add(${EXEC_NAME})