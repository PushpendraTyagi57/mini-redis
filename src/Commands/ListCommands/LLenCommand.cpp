#include "Commands/ListCommands/LLenCommand.h"
#include "Respserializer.h"

LLenCommand::LLenCommand(Store& store) : store(store)
{
}

std::string LLenCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'llen' command");
    }

    return RespSerializer::integer(store.llen(command[1]));
}