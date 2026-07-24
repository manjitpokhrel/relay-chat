cmake_minimum_required(VERSION 3.16)
project(RelayServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Windows target version to Windows 10+ for cpp-httplib
add_definitions(-D_WIN32_WINNT=0x0A00)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Core Sql)

# Find PostgreSQL
find_package(PostgreSQL REQUIRED)

# Server Source Files
set(SERVER_SOURCES
    src/main.cpp
    src/Server.cpp
    src/ServerDB.cpp
    src/ServerNetworkManager.cpp
    src/RequestHandler.cpp
    # Shared Data Models
    ../src/User.cpp
    ../src/Room.cpp
    ../src/Message.cpp
    ../src/DatabaseManager.cpp
)

# Server Header Files
set(SERVER_HEADERS
    include/Server.h
    include/ServerDB.h
    include/ServerNetworkManager.h
    include/RequestHandler.h
    ../include/User.h
    ../include/Room.h
    ../include/Message.h
    ../include/DatabaseManager.h
)

qt_add_executable(RelayServer
    ${SERVER_SOURCES}
    ${SERVER_HEADERS}
)

target_include_directories(RelayServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${PostgreSQL_INCLUDE_DIRS}
)

target_link_libraries(RelayServer PRIVATE
    Qt6::Core
    Qt6::Sql
    ${PostgreSQL_LIBRARIES}
)