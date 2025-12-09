# VaxiShare - Quick Start Guide

Get VaxiShare up and running in 5 minutes!

## Step 1: Install Dependencies

### Windows
```bash
# Install Visual Studio with C++ tools from visualstudio.microsoft.com
# Install CMake from cmake.org
# Install vcpkg package manager
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg integrate install
./vcpkg install boost
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libboost-all-dev
```

### macOS
```bash
brew install cmake boost
```

## Step 2: Download Crow Framework

```bash
cd backend

# Windows
setup_crow.bat

# Linux/Mac
chmod +x setup_crow.sh
./setup_crow.sh
```

This downloads the Crow web framework header file to `backend/lib/`.

## Step 3: Build the Project

```bash
# Create build directory
mkdir build
cd build

# Generate build files
cmake ..

# Build the project
# Windows:
cmake --build . --config Release

# Linux/Mac:
make
```

## Step 4: Run the Server

```bash
# From build directory
# Windows:
./Release/vaxishare.exe

# Linux/Mac:
./vaxishare
```

You should see:
```
VaxiShare Backend Server Starting...
Server running on http://localhost:8080
```

## Step 5: Access the Dashboard

Open your browser and navigate to:
```
http://localhost:8080
```

You should see the VaxiShare dashboard with 5 pre-configured hospitals!

## Quick Test

1. **View System Status**: Check the top cards for vaccine inventory
2. **Submit a Request**:
   - Hospital ID: `1`
   - Amount: `500`
   - Click "Submit Request"
3. **Process Allocation**:
   - Select "FCFS" from dropdown
   - Click "Process Allocation"
4. **Check Results**: See updated vaccine counts in the hospital table

## Common Issues

### Issue: "Boost not found"
**Solution (Windows):**
```bash
# Add Boost to CMake path
cmake .. -DBOOST_ROOT=C:/path/to/boost
```

**Solution (Linux/Mac):**
```bash
sudo apt-get install libboost-all-dev  # Ubuntu
brew install boost                     # macOS
```

### Issue: "crow_all.h not found"
**Solution:**
```bash
cd backend
# Run setup script again
./setup_crow.bat   # Windows
./setup_crow.sh    # Linux/Mac
```

### Issue: "Cannot connect to server"
**Solution:**
- Check if server is running on port 8080
- Try accessing: `http://127.0.0.1:8080`
- Check firewall settings

### Issue: CMake version too old
**Solution:**
```bash
# Update CMake to 3.15+
# Download from cmake.org
```

## Next Steps

- Explore different scheduling algorithms (Priority, Fair-Share, SJF)
- Add new hospitals using the API
- Monitor starvation detection
- Replenish vaccine inventory
- Read the full documentation in README.md

## Need Help?

- Check [README.md](README.md) for detailed documentation
- See [backend/README.md](backend/README.md) for API reference
- Review [PROJECT_REQUIREMENTS.md](PROJECT_REQUIREMENTS.md) for project requirements

## Pro Tips

1. **Auto-refresh**: Dashboard auto-refreshes every 5 seconds
2. **Quick requests**: Click "Request" button in hospital table for fast entry
3. **Compare algorithms**: Try different algorithms with same requests to see differences
4. **Watch metrics**: Monitor average wait time and throughput
5. **Test starvation**: Set high requests with low inventory to trigger starvation alerts

Happy allocating!
