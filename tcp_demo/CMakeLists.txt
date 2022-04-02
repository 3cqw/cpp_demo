cmake_minimum_required(VERSION 2.8)

project(tcp_demo)
set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(tcp_server tcp_server.cpp)
add_executable(tcp_client tcp_client.cpp)