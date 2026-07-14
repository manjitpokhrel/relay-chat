cmake_minimum_required(VERSION 3.16)
project(Relay VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)
find_package(OpenSSL QUIET)

set(SOURCES
    src/main.cpp
    src/User.cpp
    src/Room.cpp
    src/Message.cpp
    src/DatabaseManager.cpp
    src/LocalDataService.cpp
    src/RemoteDataService.cpp
    src/ClientNetworkManager.cpp
    src/AppController.cpp
    src/LoginWindow.cpp
    src/ChatWindow.cpp
    src/CreateRoomDialog.cpp
)

set(HEADERS
    include/BaseEntity.h
    include/User.h
    include/Room.h
    include/Message.h
    include/DatabaseManager.h
    include/IDataService.h
    include/LocalDataService.h
    include/RemoteDataService.h
    include/ClientNetworkManager.h
    include/AppController.h
    include/LoginWindow.h
    include/ChatWindow.h
    include/CreateRoomDialog.h
    include/httplib.h
)

qt_add_executable(Relay ${SOURCES} ${HEADERS})

target_link_libraries(Relay PRIVATE
    Qt6::Widgets
    Qt6::Sql
)

if(OpenSSL_FOUND)
    target_link_libraries(Relay PRIVATE
        OpenSSL::SSL
        OpenSSL::Crypto)
endif()

target_include_directories(Relay PRIVATE include)