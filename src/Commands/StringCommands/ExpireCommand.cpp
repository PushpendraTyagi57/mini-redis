#include "Commands/StringCommands/ExpireCommand.h"

#include "Respserializer.h"

#include <chrono>

ExpireCommand::ExpireCommand(Store& store)
    : store(store)
{
}

std::string ExpireCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'expire' command");
    }

    try
    {
        long long seconds = std::stoll(command[2]);

        if (seconds < 0)
        {
            return RespSerializer::error(
                "ERR invalid expire time");
        }

        bool success = store.expireKey(command[1], std::chrono::seconds(seconds));

        return RespSerializer::integer(success ? 1 : 0);
    }
    catch (...)
    {
        return RespSerializer::error(
            "ERR value is not an integer or out of range");
    }
}