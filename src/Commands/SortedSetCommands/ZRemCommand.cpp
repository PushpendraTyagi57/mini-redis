#include "Commands/SortedSetCommands/ZRemCommand.h"
#include "Respserializer.h"

ZRemCommand::ZRemCommand(Store& store)
    : store(store)
{
}

std::string ZRemCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrem' command");
    }

    int removed = 0;

    for (size_t i = 2; i < command.size(); ++i)
    {
        removed += store.zrem(command[1], command[i]);
    }

    return RespSerializer::integer(removed);
}