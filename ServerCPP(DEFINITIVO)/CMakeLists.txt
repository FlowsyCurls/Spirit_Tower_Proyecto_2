cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server src/server.cpp src/algorithms/A_Star.h src/algorithms/Bresenham.h src/algorithms/Bresenham.cpp)
if(WIN32)
    target_link_libraries(Server wsock32 ws2_32)
endif()