# VaxiShare

## Project Overview
A web-based simulation system for vaccine resource allocation across multiple hospitals, applying operating system scheduling and resource allocation algorithms to optimize equitable and efficient vaccine distribution during healthcare emergencies.

## Technical Architecture
- **Backend**: C++ with Crow/Drogon web framework
  - Implements all simulation logic, scheduling algorithms, and resource allocation
  - Provides REST API endpoints for frontend communication
  - Handles OS concepts: process scheduling, resource allocation, synchronization
- **Frontend**: HTML/CSS/JavaScript (React/Vue optional)
  - Visualizes vaccine distribution dashboard
  - Makes API calls to C++ backend
  - Displays real-time allocation data and statistics
- **Deployment**: Render or similar platform supporting C++ applications

## Core OS Concepts Applied
- **Process Scheduling** - Hospitals as processes competing for vaccine resources
- **Resource Allocation** - Fair distribution of limited vaccine inventory
- **Priority Scheduling** - Priority-based allocation for high-risk populations
- **Deadlock Prevention** - Ensuring no hospital is resource-starved
- **Synchronization** - Coordinating real-time distribution across locations

## Key Features
- Live dashboard with vaccine inventory tracking
- Multiple allocation algorithms (FCFS, Priority-based, Fair-share)
- Emergency request handling system
- Distribution fairness visualization over time
- Supply chain constraint simulation (expiration dates, transportation delays)
- Demographic-based priority modeling

## Deliverables
1. **Source Code** - GitHub repository with commented code
2. **Project Report** - Comprehensive documentation
3. **Video** - 1-2 minute demo of usage and functionalities

## Grading Breakdown

### Code (20%)
- Well-structured and readable code

### Web Hosting (10%)
- User-friendly interface

### Report (60%)
- Description of the Project (5%)
- Significance of the Project (10%)
- Code Structure (5%)
- Description of Algorithms (5%)
- Verification of Algorithms (5%)
- Functionalities (5%)
- Execution Results and Analysis (10%)
- Conclusions (5%)
- Overall Quality of Report (10%)

### GitHub (10%)
- Public repository with all project components

## Submission
- Submit GitHub repository link on Canvas (individual submission required)
