#include "Commands/SortedSetCommands/ZRangeByScoreCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZRangeByScoreCommand::ZRangeByScoreCommand(Store& store)
    : store(store)
{
}

std::string ZRangeByScoreCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrangebyscore' command");
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

        auto result = store.zrangebyscore(command[1], minScore, maxScore);

        std::vector<std::string> response;

        for (const auto& [member, score] : result)
        {
            response.push_back(member);
        }

        return RespSerializer::array(response);
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