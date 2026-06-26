cmake_minimum_required(VERSION 3.15)

project(MiniRedis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MiniRedis
    src/main.cpp
    src/Tcpserver.cpp
    src/Respparser.cpp
    src/Respserializer.cpp
    src/CommandDispatcher.cpp
    src/Store.cpp
    src/Commands/CommandCommand.cpp
    src/Commands/EchoCommand.cpp
    src/Commands/PingCommand.cpp
    src/Commands/SetCommand.cpp
    src/Commands/GetCommand.cpp
    src/Commands/DelCommand.cpp
)