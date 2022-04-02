cmake_minimum_required(VERSION 2.8)

project(opc_ua_demo)
#set(CMAKE_CXX_FLAGS "-std=c++11")

#find_package(MbedTLS REQUIRED)
#find_package(open62541 REQUIRED)

add_definitions(-DUA_ENABLE_SUBSCRIPTIONS_EVENTS)

add_executable(opc_ua_server opc_ua_server.cpp)
add_executable(opc_ua_client opc_ua_client.cpp)
add_executable(opc_ua_server_oo opc_ua_server_oo.cpp)

target_link_libraries(opc_ua_server open62541)
target_link_libraries(opc_ua_client open62541)
target_link_libraries(opc_ua_server_oo open62541)