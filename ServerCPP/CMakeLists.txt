cmake_minimum_required(VERSION 3.16)
project(Server)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server server.cpp A_Star.h)
if(WIN32)
    target_link_libraries(Server wsock32 ws2_32)
endif()