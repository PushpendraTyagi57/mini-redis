#include "Commands/SortedSetCommands/ZRangeCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZRangeCommand::ZRangeCommand(Store& store)
    : store(store)
{
}

std::string ZRangeCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4 && command.size() != 5)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrange' command");
    }

    bool withScores = (command.size() == 5 && command[4] == "WITHSCORES");

    try
    {
        int start = std::stoi(command[2]);
        int stop = std::stoi(command[3]);

        auto result = store.zrange(command[1], start, stop);

        std::vector<std::string> response;

        for (const auto& [member, score] : result)
        {
            response.push_back(member);
            if (withScores)
            {
                response.push_back(std::to_string(score));
            }
        }

        return RespSerializer::array(response);
    }
    catch (...)
    {
        return RespSerializer::error("ERR value is not an integer");
    }
}