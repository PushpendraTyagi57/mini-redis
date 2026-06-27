#include "Commands/GeneralCommands/PingCommand.h"
#include "Respserializer.h"

std::string PingCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() == 1)
    {
        return RespSerializer::simpleString("PONG");
    }

    if (command.size() == 2)
    {
        return RespSerializer::bulkString(command[1]);
    }

    return RespSerializer::error(
        "ERR wrong number of arguments for 'ping' command");
}