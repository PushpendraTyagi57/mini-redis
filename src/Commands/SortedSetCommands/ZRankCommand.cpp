#include "Commands/SortedSetCommands/ZRankCommand.h"
#include "Respserializer.h"

ZRankCommand::ZRankCommand(Store& store)
    : store(store)
{
}

std::string ZRankCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrank' command");
    }

    auto rank = store.zrank(command[1], command[2]);

    if (!rank.has_value())
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::integer(*rank);
}