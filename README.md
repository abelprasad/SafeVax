# VaxiShare

A web-based simulation system for vaccine resource allocation across multiple hospitals, applying operating system scheduling and resource allocation algorithms to optimize equitable and efficient vaccine distribution during healthcare emergencies.

## Technical Architecture

**Backend**: C++ with Crow web framework
- Implements all simulation logic, scheduling algorithms, and resource allocation
- Provides REST API endpoints for frontend communication
- Handles OS concepts: process scheduling, resource allocation, synchronization

**Frontend**: HTML/CSS/JavaScript
- Visualizes vaccine distribution dashboard
- Makes API calls to C++ backend
- Displays real-time allocation data and statistics

## Project Structure

```
VaxiShare/
├── backend/                    # C++ Backend
│   ├── include/               # Header files
│   │   ├── Hospital.h         # Hospital class (process representation)
│   │   ├── VaccineAllocator.h # Resource allocator
│   │   └── Scheduler.h        # Process scheduler
│   ├── src/                   # Implementation files
│   │   ├── Hospital.cpp
│   │   ├── VaccineAllocator.cpp
│   │   ├── Scheduler.cpp
│   │   └── main.cpp           # REST API server
│   ├── lib/                   # Libraries (Crow header)
│   ├── CMakeLists.txt         # Build configuration
│   ├── setup_crow.bat         # Windows setup script
│   ├── setup_crow.sh          # Linux/Mac setup script
│   └── README.md              # Backend documentation
├── frontend/                  # Web Frontend
│   ├── index.html             # Main dashboard
│   ├── css/
│   │   └── style.css          # Styles
│   ├── js/
│   │   └── app.js             # API interactions
│   └── assets/                # Images, icons
├── PROJECT_REQUIREMENTS.md    # Project requirements
├── README.md                  # This file
└── LICENSE
```

## Core OS Concepts Applied

### 1. Process Scheduling
- **Hospitals as Processes**: Each hospital is modeled as a process competing for vaccine resources
- **Multiple Scheduling Algorithms**:
  - **FCFS (First-Come-First-Served)**: Requests processed in order received
  - **Priority-Based**: Hospitals with higher priority (more high-risk population) served first
  - **Fair-Share**: Proportional allocation based on demand
  - **SJF (Shortest Job First)**: Smallest requests processed first

### 2. Resource Allocation
- Vaccines treated as limited system resources
- Mutex-based synchronization for thread-safe allocation
- Dynamic resource management with replenishment

### 3. Priority Scheduling
- Priority levels based on high-risk population size
- Emergency request handling with priority boost

### 4. Deadlock Prevention
- Starvation detection algorithm
- Minimum allocation guarantee to prevent indefinite postponement
- Wait time tracking for fairness metrics

### 5. Synchronization
- Mutex locks for concurrent access protection
- Thread-safe operations across multiple allocation requests
- Race condition prevention in resource management

## Quick Start

### Prerequisites

**Windows:**
- Visual Studio with C++ tools
- CMake (3.15+)
- Boost libraries (install via vcpkg)

**Linux/Mac:**
```bash
# Ubuntu/Debian
sudo apt-get install build-essential cmake libboost-all-dev

# macOS
brew install cmake boost
```

### Setup & Run

1. **Clone the repository**
```bash
git clone <your-repo-url>
cd VaxiShare
```

2. **Setup backend**
```bash
cd backend

# Windows
setup_crow.bat

# Linux/Mac
chmod +x setup_crow.sh
./setup_crow.sh
```

3. **Build backend**
```bash
mkdir build
cd build
cmake ..

# Windows (Visual Studio)
cmake --build .

# Linux/Mac
make
```

4. **Run the server**
```bash
./vaxishare  # or vaxishare.exe on Windows
```

Server starts on `http://localhost:8080`

5. **Open frontend**
- Navigate to `http://localhost:8080` in your browser
- Or open `frontend/index.html` directly

## Features

### Live Dashboard
- Real-time vaccine inventory tracking
- System status metrics (availability, wait times, throughput)
- Starvation detection alerts

### Multiple Allocation Algorithms
- Switch between FCFS, Priority, Fair-Share, and SJF
- Compare algorithm performance in real-time
- Visual feedback on allocation results

### Emergency Request Handling
- Submit vaccine requests for any hospital
- Priority-based emergency processing
- Request queue management

### Distribution Fairness Visualization
- Hospital status table with detailed metrics
- Wait time tracking per hospital
- Resource utilization statistics

### Deadlock Prevention
- Automatic starvation detection
- Minimum allocation guarantee
- Prevention mechanisms visualization

## API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/api/status` | System status and metrics |
| GET | `/api/hospitals` | List all hospitals |
| POST | `/api/request` | Submit vaccine request |
| POST | `/api/allocate` | Process allocation with algorithm |
| POST | `/api/replenish` | Add vaccines to inventory |
| POST | `/api/hospital` | Add new hospital |
| GET | `/api/metrics` | Scheduling performance metrics |

See [backend/README.md](backend/README.md) for detailed API documentation.

## Usage Examples

### Submit a Vaccine Request
1. Enter Hospital ID and amount in the request form
2. Click "Submit Request"
3. Request added to queue

### Process Allocation
1. Select scheduling algorithm from dropdown
2. Click "Process Allocation"
3. View updated hospital statuses

### Replenish Vaccines
1. Enter amount in replenish field
2. Click "Replenish"
3. Inventory updated

## Grading Criteria

- **Code (20%)**: Well-structured C++ implementation
- **Web Hosting (10%)**: User-friendly web interface
- **Report (60%)**: Comprehensive documentation
- **GitHub (10%)**: Public repository with all components

## Deliverables

1. ✅ **Source Code**: Complete C++ backend and web frontend
2. ⏳ **Project Report**: Detailed documentation (see PROJECT_REQUIREMENTS.md)
3. ⏳ **Demo Video**: 1-2 minute usage demonstration

## Development

### Adding New Hospitals
```cpp
// In main.cpp
allocator.addHospital(std::make_shared<Hospital>(
    6,                  // ID
    "New Hospital",     // Name
    3,                  // Priority (1-5)
    4000                // High-risk population
));
```

### Implementing New Algorithms
1. Add algorithm to `VaccineAllocator::AllocationAlgorithm` enum
2. Implement allocation logic in `VaccineAllocator.cpp`
3. Update API endpoint in `main.cpp`
4. Add option to frontend dropdown

## Testing

### Manual Testing
1. Start server
2. Open browser at `http://localhost:8080`
3. Submit various requests
4. Test different allocation algorithms
5. Verify starvation detection

### Metrics to Monitor
- Average wait time
- Throughput (requests/time)
- Starvation incidents
- Resource utilization

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Operating Systems course materials
- Crow C++ web framework
- Boost libraries
