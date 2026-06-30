#include "Commands/SortedSetCommands/ZAddCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZAddCommand::ZAddCommand(Store& store)
    : store(store)
{
}

std::string ZAddCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() < 4 || command.size() % 2 != 0)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'zadd' command");
    }

    const std::string& key = command[1];
    int added = 0;

    for (size_t i = 2; i < command.size(); i += 2)
    {
        const std::string& scoreStr = command[i];
        const std::string& member   = command[i + 1];

        try
        {
            size_t pos;
            double score = std::stod(scoreStr, &pos);

            if (pos != scoreStr.size())
            {
                return RespSerializer::error(
                    "ERR value is not a valid float");
            }

            added += store.zadd(key, score, member);
        }
        catch (const std::invalid_argument& e)
        {
            return RespSerializer::error(
                "ERR value is not a valid float");
        }
        catch (const std::out_of_range& e)
        {
            return RespSerializer::error(
                "ERR value is out of range");
        }
    }

    return RespSerializer::integer(added);
}