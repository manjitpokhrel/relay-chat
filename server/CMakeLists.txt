cmake_minimum_required(VERSION 3.16)
project(RelayServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt MOC processing for headers
set(CMAKE_AUTOMOC ON)

# Find required Qt6 and PostgreSQL dependencies
find_package(Qt6 COMPONENTS Core Network Sql REQUIRED)
find_package(PostgreSQL REQUIRED)

# Collect source files
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.h" 
    "include/*.h" 
    "include/*.hpp" 
    "*.cpp" 
    "*.h"
)

add_executable(RelayServer ${SOURCES})

# Include headers (including PostgreSQL include directory)
target_include_directories(RelayServer PRIVATE 
    include 
    src 
    ${PostgreSQL_INCLUDE_DIRS}
)

# Link Qt6 modules and PostgreSQL libraries
target_link_libraries(RelayServer PRIVATE 
    Qt6::Core 
    Qt6::Network 
    Qt6::Sql 
    ${PostgreSQL_LIBRARIES}
)