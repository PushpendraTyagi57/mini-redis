#include "Commands/ListCommands/LPushCommand.h"
#include "Respserializer.h"

LPushCommand::LPushCommand(Store& store) : store(store)
{
}

std::string LPushCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'lpush' command");
    }

    std::vector<std::string> elements(command.begin() + 2, command.end());
    for (const auto& element : elements)
    {
        store.lpush(command[1], element);
    }

    return RespSerializer::integer(store.llen(command[1]));
}