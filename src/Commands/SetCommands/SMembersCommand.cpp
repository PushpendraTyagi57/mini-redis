#include "Commands/SetCommands/SMembersCommand.h"
#include "Respserializer.h"

SMembersCommand::SMembersCommand(Store& store) : store(store)
{
}

std::string SMembersCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'smembers' command");
    }

    const std::string& key = command[1];

    auto members = store.smembers(key);

    std::vector<std::string> response(members.begin(), members.end());

    return RespSerializer::array(response);
}