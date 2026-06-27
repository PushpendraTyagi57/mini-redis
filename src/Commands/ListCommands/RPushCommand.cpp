#include "Commands/ListCommands/RPushCommand.h"
#include "Respserializer.h"

RPushCommand::RPushCommand(Store& store) : store(store)
{
}

std::string RPushCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'rpush' command");
    }

    std::vector<std::string> elements(command.begin() + 2, command.end());
    for (const auto& element : elements)
    {
        store.rpush(command[1], element);
    }

    return RespSerializer::integer(store.llen(command[1]));
}