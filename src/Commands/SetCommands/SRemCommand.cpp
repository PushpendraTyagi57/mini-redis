#include "Commands/SetCommands/SRemCommand.h"
#include "Respserializer.h"

SRemCommand::SRemCommand(Store& store) : store(store)
{
}

std::string SRemCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'srem' command");
    }

    const std::string& key = command[1];
    int count = 0;

    for (size_t i = 2; i < command.size(); ++i)
    {
        count += store.srem(key, command[i]);
    }

    return RespSerializer::integer(count);
}