#include "Commands/SetCommand.h"
#include "Respserializer.h"

SetCommand::SetCommand(Store& store)
    : store(store)
{
}

std::string SetCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 3)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'set' command");
    }

    store.setString(command[1], command[2]);

    return RespSerializer::simpleString("OK");
}