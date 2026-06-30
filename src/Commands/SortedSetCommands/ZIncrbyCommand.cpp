#include "Commands/SortedSetCommands/ZIncrbyCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZIncrbyCommand::ZIncrbyCommand(Store& store)
    : store(store)
{
}

std::string ZIncrbyCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zincrby' command");
    }

    try
    {
        size_t pos;

        double increment = std::stod(command[2], &pos);

        if (pos != command[2].size())
        {
            return RespSerializer::error("ERR value is not a valid float");
        }

        double newScore = store.zincrby(command[1], increment, command[3]);

        return RespSerializer::bulkString(std::to_string(newScore));
    }
    catch (const std::invalid_argument& e)
    {
        return RespSerializer::error("ERR value is not a valid float");
    }
    catch (const std::out_of_range& e)
    {
        return RespSerializer::error("ERR value is out of range");
    }
}