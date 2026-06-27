#include "Commands/ListCommands/LRangeCommand.h"
#include "Respserializer.h"

LRangeCommand::LRangeCommand(Store& store) : store(store)
{
}

std::string LRangeCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 4)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'lrange' command");
    }

    int start = std::stoi(command[2]);
    int end = std::stoi(command[3]);

    auto elements = store.lrange(command[1], start, end);
    return RespSerializer::array(elements);
}