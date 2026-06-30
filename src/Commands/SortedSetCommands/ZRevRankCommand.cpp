#include "Commands/SortedSetCommands/ZRevRankCommand.h"
#include "Respserializer.h"

ZRevRankCommand::ZRevRankCommand(Store& store)
    : store(store)
{
}

std::string ZRevRankCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrevrank' command");
    }

    auto rank = store.zrevrank(command[1], command[2]);

    if (!rank.has_value())
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::integer(*rank);
}