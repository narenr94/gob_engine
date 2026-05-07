include(GoogleTest)

set(SRC_ROOT "../../../")

include_directories(${SRC_ROOT}/include)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(ACT_SRCS ${SRC_ROOT}/src/character.cpp)

# Base Character Tests
set(EXEC_NAME characterTests)
set(TEST_SOURCES characterTests.cpp)
add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS})
target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})
utest_run_add(${EXEC_NAME})

# Human Character Tests (Warrior, Mage, Ranger)
set(EXEC_NAME humanCharacterTests)
set(TEST_SOURCES humanCharacterTests.cpp)
add_executable(${EXEC_NAME}
               ${TEST_SOURCES}
               ${ACT_SRCS})
target_link_libraries(${EXEC_NAME} ${GMOCK_LINK_LIBRARIES} ${GTEST_LINK_LIBRARIES})
utest_run_add(${EXEC_NAME})