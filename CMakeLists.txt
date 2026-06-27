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
    src/Commands/GeneralCommands/EchoCommand.cpp
    src/Commands/GeneralCommands/PingCommand.cpp
    src/Commands/GeneralCommands/CommandCommand.cpp
    src/Commands/StringCommands/SetCommand.cpp
    src/Commands/StringCommands/GetCommand.cpp
    src/Commands/StringCommands/DelCommand.cpp
    src/Commands/StringCommands/ExpireCommand.cpp
    src/Commands/StringCommands/TtlCommand.cpp
    src/Commands/StringCommands/SetexCommand.cpp
    src/Commands/ListCommands/LPushCommand.cpp
    src/Commands/ListCommands/RPushCommand.cpp
    src/Commands/ListCommands/LPopCommand.cpp
    src/Commands/ListCommands/RPopCommand.cpp
    src/Commands/ListCommands/LLenCommand.cpp
    src/Commands/ListCommands/LRangeCommand.cpp
)