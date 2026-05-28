cmake_minimum_required(VERSION 3.10.3)

project(UnitTests)

include(CTest)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTEST REQUIRED gtest)
pkg_check_modules(GMOCK REQUIRED gmock)

function(utest_run_add test_suite)
	add_test(NAME ${test_suite} COMMAND ${test_suite})
endfunction()

add_subdirectory(gameData)
add_subdirectory(commonJsonParser)
add_subdirectory(defines)
add_subdirectory(log)
add_subdirectory(playerInput)
add_subdirectory(randomize)
add_subdirectory(utilities)


