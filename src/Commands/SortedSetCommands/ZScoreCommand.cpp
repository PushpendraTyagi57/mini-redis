#include "Commands/SortedSetCommands/ZScoreCommand.h"
#include "Respserializer.h"

ZScoreCommand::ZScoreCommand(Store& store)
    : store(store)
{
}

std::string ZScoreCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zscore' command");
    }

    auto score = store.zscore(command[1], command[2]);

    if (!score.has_value())
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::bulkString(std::to_string(*score));
}