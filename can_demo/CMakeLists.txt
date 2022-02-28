cmake_minimum_required(VERSION 2.8)

project(can_demo)
set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(can_sender can_sender.cpp)
add_executable(can_receiver can_receiver.cpp)
