cmake_minimum_required(VERSION 3.15)
project(VaxiShare)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)
include_directories(lib)

# Source files
set(SOURCES
    src/main.cpp
    src/Hospital.cpp
    src/VaccineAllocator.cpp
    src/Scheduler.cpp
)

# Executable
add_executable(vaxishare ${SOURCES})

# cpp-httplib is header-only, only needs threading
find_package(Threads REQUIRED)

target_link_libraries(vaxishare
    Threads::Threads
)

# Platform-specific libraries
if(WIN32)
    target_link_libraries(vaxishare ws2_32)
endif()

# Enable warnings
if(MSVC)
    target_compile_options(vaxishare PRIVATE /W4)
    add_definitions(-D_WIN32_WINNT=0x0A00)
else()
    target_compile_options(vaxishare PRIVATE -Wall -Wextra -pedantic)
endif()
