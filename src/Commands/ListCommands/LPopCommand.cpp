#include "Commands/ListCommands/LPopCommand.h"
#include "Respserializer.h"

LPopCommand::LPopCommand(Store& store) : store(store)
{
}

std::string LPopCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'lpop' command");
    }

    auto element = store.lpop(command[1]);
    if (element.has_value() == false)
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::bulkString(element.value());
}