#include "Commands/HashCommands/HGetCommand.h"
#include "Respserializer.h"

HGetCommand::HGetCommand(Store& store) : store(store)
{
}

std::string HGetCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'hget' command");
    }

    const std::string& key = command[1];
    const std::string& field = command[2];

    auto value = store.hget(key, field);

    if (value)
    {
        return RespSerializer::bulkString(*value);
    }
    else
    {
        return RespSerializer::nullBulkString();
    }
}