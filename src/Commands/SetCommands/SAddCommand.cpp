#include "Commands/SetCommands/SAddCommand.h"
#include "Respserializer.h"

SAddCommand::SAddCommand(Store& store) : store(store)
{
}

std::string SAddCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'sadd' command");
    }

    const std::string& key = command[1];
    int count = 0;

    for (size_t i = 2; i < command.size(); ++i)
    {
        count += store.sadd(key, command[i]);
    }

    return RespSerializer::integer(count);
}