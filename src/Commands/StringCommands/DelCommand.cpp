#include "Commands/StringCommands/DelCommand.h"
#include "Respserializer.h"

DelCommand::DelCommand(Store& store)
    : store(store)
{
}

std::string DelCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'del' command");
    }

    bool deleted = store.deleteKey(command[1]);

    return RespSerializer::integer(deleted ? 1 : 0);
}