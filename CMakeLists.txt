cmake_minimum_required(VERSION 3.15)

project(MiniRedis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include
    src
)

add_executable(MiniRedis
    src/main.cpp
    src/Tcpserver.cpp
    src/Respparser.cpp
    src/Respserializer.cpp
    src/CommandDispatcher.cpp
    src/Store/Store.cpp
    src/Store/StringStore.cpp
    src/Store/ListStore.cpp
    src/Store/HashStore.cpp
    src/Store/SetStore.cpp
    src/Store/SortedSetStore.cpp
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
    src/Commands/HashCommands/HSetCommand.cpp
    src/Commands/HashCommands/HGetCommand.cpp
    src/Commands/HashCommands/HGetAllCommand.cpp
    src/Commands/HashCommands/HDelCommand.cpp
    src/Commands/SetCommands/SAddCommand.cpp
    src/Commands/SetCommands/SRemCommand.cpp
    src/Commands/SetCommands/SMembersCommand.cpp
    src/Commands/SetCommands/SIsMemberCommand.cpp
    src/Commands/SortedSetCommands/ZAddCommand.cpp
    src/Commands/SortedSetCommands/ZRangeCommand.cpp
    src/Commands/SortedSetCommands/ZRevRangeCommand.cpp
    src/Commands/SortedSetCommands/ZIncrbyCommand.cpp
    src/Commands/SortedSetCommands/ZRemCommand.cpp
    src/Commands/SortedSetCommands/ZScoreCommand.cpp
    src/Commands/SortedSetCommands/ZCardCommand.cpp
    src/Commands/SortedSetCommands/ZRankCommand.cpp
    src/Commands/SortedSetCommands/ZRevRankCommand.cpp
    src/Commands/SortedSetCommands/ZRangeByScoreCommand.cpp
    src/Commands/SortedSetCommands/ZCountCommand.cpp
)