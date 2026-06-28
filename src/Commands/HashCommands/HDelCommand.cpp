#include "Commands/HashCommands/HDelCommand.h"
#include "Respserializer.h"

HDelCommand::HDelCommand(Store& store) : store(store)
{
}

std::string HDelCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'hdel' command");
    }

    const std::string& key = command[1];

    int count = 0;

    for (size_t i = 2; i < command.size(); ++i)
    {
        count += store.hdel(key, command[i]);
    }

    return RespSerializer::integer(count);
}