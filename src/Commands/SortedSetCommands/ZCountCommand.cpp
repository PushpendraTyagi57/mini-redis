#include "Commands/SortedSetCommands/ZCountCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZCountCommand::ZCountCommand(Store& store)
    : store(store)
{
}

std::string ZCountCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zcount' command");
    }

    try
    {
        size_t pos1, pos2;

        double minScore = std::stod(command[2], &pos1);
        double maxScore = std::stod(command[3], &pos2);

        if (pos1 != command[2].size() || pos2 != command[3].size())
        {
            return RespSerializer::error("ERR value is not a valid float");
        }

        int count = store.zcount(command[1], minScore, maxScore);
        return RespSerializer::integer(count);
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