cmake_minimum_required(VERSION 2.8)

project(udp_demo)
set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(udp_server udp_server.cpp)
add_executable(udp_client udp_client.cpp)
