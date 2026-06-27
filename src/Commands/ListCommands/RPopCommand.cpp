#include "Commands/ListCommands/RPopCommand.h"
#include "Respserializer.h"

RPopCommand::RPopCommand(Store& store) : store(store)
{
}

std::string RPopCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'rpop' command");
    }

    auto element = store.rpop(command[1]);
    if (element.has_value() == false)
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::bulkString(element.value());
}