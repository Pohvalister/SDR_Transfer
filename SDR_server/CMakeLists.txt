cmake_minimum_required(VERSION 3.5)

project(SDR_server)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(RTL_SDR_LIB REQUIRED IMPORTED_TARGET librtlsdr)

#find_library(RTL_SDR_LIB -L/usr/local/lib -lrtlsdr -lusb-1.0)


set(SOURCE_FILES
    main.cpp connection_handler.cpp connection_handler.h device_listener.cpp device_listener.h convenience.c convenience.h
    ../connection_structure.h)

add_executable(SDR_server ${SOURCE_FILES})

target_link_libraries(SDR_server PUBLIC
    PkgConfig::RTL_SDR_LIB)
