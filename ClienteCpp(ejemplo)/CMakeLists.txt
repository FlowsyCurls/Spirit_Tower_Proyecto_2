cmake_minimum_required(VERSION 3.16)
project(ClienteCPP_ejemplo_)

set(CMAKE_CXX_STANDARD 14)

add_executable(ClienteCPP_ejemplo_ main.cpp)
if(WIN32)
    target_link_libraries(ClienteCPP_ejemplo_ wsock32 ws2_32)
endif()