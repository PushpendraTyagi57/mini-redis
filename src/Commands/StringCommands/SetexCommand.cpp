#include "Commands/StringCommands/SetexCommand.h"

#include "Respserializer.h"

#include <chrono>
#include <stdexcept>

SetexCommand::SetexCommand(Store& store)
    : store(store)
{
}

std::string SetexCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'setex' command");
    }

    try
    {
        long long seconds = std::stoll(command[2]);

        if (seconds < 0)
        {
            return RespSerializer::error("ERR invalid expire time");
        }

        store.setex(command[1], std::chrono::seconds(seconds), command[3]);

        return RespSerializer::simpleString("OK");
    }

    catch (const std::invalid_argument&)
    {
        return RespSerializer::error("ERR value is not an integer or out of range");
    }

    catch (const std::out_of_range&)
    {
        return RespSerializer::error("ERR value is not an integer or out of range");
    }
}