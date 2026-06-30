#include "Commands/SortedSetCommands/ZCardCommand.h"
#include "Respserializer.h"

ZCardCommand::ZCardCommand(Store& store)
    : store(store)
{
}

std::string ZCardCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zcard' command");
    }

    int count = store.zcard(command[1]);
    return RespSerializer::integer(count);
}