#include "Commands/SetCommands/SIsMemberCommand.h"
#include "Respserializer.h"

SIsMemberCommand::SIsMemberCommand(Store& store) : store(store)
{
}

std::string SIsMemberCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'sismember' command");
    }

    const std::string& key = command[1];
    const std::string& member = command[2];

    return RespSerializer::integer(store.sismember(key, member));
}