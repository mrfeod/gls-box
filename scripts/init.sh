#!/bin/bash

set -euo pipefail

# Check if pip is installed
if ! command -v pip &> /dev/null; then
  echo "Error: pip is not installed. Please install it and try again."
  exit 1
fi

# Install dependencies
pip install -r requirements.txt

# Init conan
if conan profile list | grep -q "default"; then
  echo "Profile found"
else
  conan profile detect
fi