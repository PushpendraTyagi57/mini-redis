#include "Commands/GetCommand.h"
#include "Respserializer.h"

GetCommand::GetCommand(Store& store)
    : store(store)
{
}

std::string GetCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'get' command");
    }

    auto value = store.getString(command[1]);

    if (!value.has_value())
    {
        return RespSerializer::nullBulkString();
    }

    return RespSerializer::bulkString(value.value());
}