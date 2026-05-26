#!/bin/bash

set -e

mkdir -p build

cd build

# Create include and lib directories
mkdir -p include
mkdir -p lib

# Download and install gtest/gmock if not already present
if [ ! -d "googletest" ]; then
    echo "Downloading Google Test and Google Mock..."
    git clone https://github.com/google/googletest.git
    cd googletest
    mkdir -p build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=../.. ..
    make
    make install
    echo "Google Test and Google Mock installed successfully"
    cd ../..
else
    echo "Google Test and Google Mock already present"
fi
BUILD_DIR=$PWD
PKG_CONFIG_PATH=${BUILD_DIR}/lib/pkgconfig cmake ../ -DCOVERAGE_ENABLED=ON -DCMAKE_BUILD_TYPE=Debug -DCMAKE_LIBRARY_PATH=${BUILD_DIR}/lib -B$PWD

make

# Disable exit on error for test execution
set +e

# Run all test executables
echo ""
echo "==================================="
echo "Running All Tests..."
echo "==================================="

# Initialize counters and failed tests array
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
FAILED_TEST_NAMES=()

# Find and run all test executables (excluding googletest's own tests)
while IFS= read -r test_exe; do
    # Skip googletest directory
    if [[ "$test_exe" != *"googletest"* ]]; then
        echo ""
        echo "Running: $test_exe"
        echo "-----------------------------------"
        if "$test_exe"; then
            ((PASSED_TESTS++))
        else
            ((FAILED_TESTS++))
            FAILED_TEST_NAMES+=("$test_exe")
        fi
        ((TOTAL_TESTS++))
    fi
done < <(find . -type f -executable \( -name "*Tests" -o -name "*Test" \))

# Print summary
echo ""
echo "==================================="
echo "TEST SUMMARY"
echo "==================================="
echo "Total Tests Run: $TOTAL_TESTS"
echo "Total Successes: $PASSED_TESTS"
echo "Total Failures: $FAILED_TESTS"

if [ $FAILED_TESTS -gt 0 ]; then
    echo ""
    echo "Failed Tests:"
    for failed_test in "${FAILED_TEST_NAMES[@]}"; do
        echo "  - $failed_test"
    done
    echo "==================================="
    exit 1
else
    echo "==================================="
    echo "All Tests Passed Successfully!"
    echo "==================================="
fi

echo ""
