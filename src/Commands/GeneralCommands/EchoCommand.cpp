#include "Commands/GeneralCommands/EchoCommand.h"
#include "Respserializer.h"

std::string EchoCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'echo' command");
    }

    return RespSerializer::bulkString(command[1]);
}