#include "Commands/HashCommands/HSetCommand.h"
#include "Respserializer.h"

HSetCommand::HSetCommand(Store& store) : store(store)
{
}

std::string HSetCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 4 || command.size() % 2 != 0)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'hset' command");
    }

    const std::string& key = command[1];

    int count = 0;

    for (size_t i = 2; i < command.size(); i += 2)
    {
        count += store.hset(key, command[i], command[i + 1]);
    }

    return RespSerializer::integer(count);
}