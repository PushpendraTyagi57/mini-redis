cmake_minimum_required(VERSION 3.15)

project(MiniRedis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MiniRedis
    src/main.cpp
    src/TcpServer.cpp
)