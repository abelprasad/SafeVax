# VaxiShare Backend (C++)

## Setup Instructions

### Prerequisites
1. **C++ Compiler** (GCC, Clang, or MSVC with C++17 support)
2. **CMake** (version 3.15 or higher)
3. **Boost Libraries** (for Crow framework)
4. **Crow Framework** (header-only, will be downloaded)

### Installation

#### Windows

1. Install Visual Studio with C++ tools
2. Install CMake from https://cmake.org/
3. Install Boost:
   ```bash
   # Using vcpkg (recommended)
   vcpkg install boost
   ```

4. Download Crow header:
   ```bash
   cd backend
   setup_crow.bat
   ```

5. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

#### Linux/Mac

1. Install dependencies:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install build-essential cmake libboost-all-dev

   # macOS
   brew install cmake boost
   ```

2. Download Crow header:
   ```bash
   cd backend
   chmod +x setup_crow.sh
   ./setup_crow.sh
   ```

3. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

### Running the Server

```bash
cd build
./vaxishare
```

Server will start on `http://localhost:8080`

## API Endpoints

### GET /api/status
Returns overall system status including total vaccines, available vaccines, and metrics.

**Response:**
```json
{
  "totalVaccines": 10000,
  "availableVaccines": 5000,
  "averageWaitTime": 2.5,
  "throughput": 15.3,
  "hasStarvation": false
}
```

### GET /api/hospitals
Returns list of all hospitals and their current state.

**Response:**
```json
{
  "hospitals": [
    {
      "id": 1,
      "name": "City General Hospital",
      "priority": 3,
      "currentVaccines": 1000,
      "requestedVaccines": 500,
      "highRiskPopulation": 5000,
      "waitTime": 2.0,
      "need": 1.5,
      "isStarved": false
    }
  ]
}
```

### POST /api/request
Add a vaccine request from a hospital.

**Request:**
```json
{
  "hospitalId": 1,
  "amount": 500
}
```

### POST /api/allocate
Process allocation using specified algorithm.

**Request:**
```json
{
  "algorithm": "FCFS"  // Options: FCFS, PRIORITY, FAIR_SHARE, SJF
}
```

### POST /api/replenish
Add vaccines to inventory.

**Request:**
```json
{
  "amount": 1000
}
```

### POST /api/hospital
Add a new hospital to the system.

**Request:**
```json
{
  "id": 6,
  "name": "New Hospital",
  "priority": 3,
  "highRiskPopulation": 3000
}
```

### GET /api/metrics
Get scheduling performance metrics.

**Response:**
```json
{
  "averageWaitTime": 2.5,
  "throughput": 15.3
}
```

## OS Concepts Implemented

### Process Scheduling
- Hospitals represented as processes
- Multiple scheduling algorithms (FCFS, Priority, Fair-Share, SJF)

### Resource Allocation
- Vaccines as limited resources
- Mutex-based synchronization for thread-safe allocation

### Deadlock Prevention
- Starvation detection
- Minimum allocation guarantee

### Synchronization
- Mutex locks for concurrent access
- Thread-safe operations
