#!/bin/bash -e

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

# Run all test executables
echo ""
echo "==================================="
echo "Running All Tests..."
echo "==================================="

# Find and run all test executables (excluding googletest's own tests)
find . -type f -executable -name "*Tests" -o -type f -executable -name "*Test" | while read test_exe; do
    # Skip googletest directory
    if [[ "$test_exe" != *"googletest"* ]]; then
        echo ""
        echo "Running: $test_exe"
        echo "-----------------------------------"
        "$test_exe"
    fi
done

echo ""
echo "==================================="
echo "All Tests Completed"
echo "==================================="

