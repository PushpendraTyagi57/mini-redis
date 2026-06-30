#include "Commands/SortedSetCommands/ZRevRangeCommand.h"
#include "Respserializer.h"

#include <string>
#include <stdexcept>

ZRevRangeCommand::ZRevRangeCommand(Store& store)
    : store(store)
{
}

std::string ZRevRangeCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4 && command.size() != 5)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'zrevrange' command");
    }

    bool withScores = (command.size() == 5 && command[4] == "WITHSCORES");

    try
    {
        int start = std::stoi(command[2]);
        int stop = std::stoi(command[3]);

        auto result = store.zrevrange(command[1], start, stop);

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