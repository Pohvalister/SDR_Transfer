cmake_minimum_required(VERSION 3.5)

project(SDR_server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp connection_handler.cpp connection_handler.h device_listener.cpp device_listener.h)

add_executable(SDR_server ${SOURCE_FILES})
