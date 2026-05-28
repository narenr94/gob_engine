include(GoogleTest)

set(SRC_ROOT "../../../")
set(FAKE_ROOT "../fakes/")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(ACT_SRCS ${SRC_ROOT}/src/defines.cpp
             ${SRC_ROOT}/src/utilities.cpp
             ${SRC_ROOT}/src/pack.cpp)

set(FAKE_SRCS ${FAKE_ROOT}/fakeCharacter.cpp
               ${FAKE_ROOT}/fakeLog.cpp
               ${FAKE_ROOT}/fakePlayerInput.cpp
               ${FAKE_ROOT}/fakeRandomize.cpp
               ${FAKE_ROOT}/fakeRace.cpp)

# Defines Tests
set(EXEC_NAME definesTests)

set(TEST_SOURCES definesTests.cpp)

add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS}
               ${FAKE_SRCS})

target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})

utest_run_add(${EXEC_NAME})
