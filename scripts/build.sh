#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
  echo "Error: CMake is not installed. Please install it and try again."
  exit 1
fi

# Check if Conan is installed
if ! command -v conan &> /dev/null; then
  echo "Error: Conan is not installed. Please install it and try again."
  exit 1
fi

# Default build type
BUILD_TYPE="Release"

# Parse command line arguments
while [[ $# -gt 0 ]]; do
  case $1 in
    --debug|-d)
      BUILD_TYPE="Debug"
      shift
      ;;
    *)
      echo "Unknown option: $1"
      echo "Usage: $0 [--debug|-d]"
      exit 1
      ;;
  esac
done

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Install dependencies with Conan
if [[ "$BUILD_TYPE" == "Debug" ]]; then
    conan install .. --output-folder=. --build=missing -s build_type=Debug
else
    conan install .. --output-folder=. --build=missing
fi

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Build the project
cmake --build . --config $BUILD_TYPE

# Run the application
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" ]]; then
    # Windows
    cd ./$BUILD_TYPE
    ./gls-box.exe
else
    # Linux/macOS
    ./gls-box
fi