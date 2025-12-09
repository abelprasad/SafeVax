#!/bin/bash

# Download Crow header-only library

echo "Downloading Crow C++ web framework..."

# Create lib directory if it doesn't exist
mkdir -p lib
cd lib

# Download crow_all.h (single header version)
curl -L -o crow_all.h https://raw.githubusercontent.com/CrowCpp/Crow/master/include/crow_all.h

echo "Crow downloaded successfully to backend/lib/crow_all.h"
echo ""
echo "Next steps:"
echo "1. Install Boost: sudo apt-get install libboost-all-dev (Ubuntu) or brew install boost (macOS)"
echo "2. Build: mkdir build && cd build && cmake .. && make"

cd ..
