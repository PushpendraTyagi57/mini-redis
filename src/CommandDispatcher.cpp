#include "CommandDispatcher.h"

#include "Commands/PingCommand.h"
#include "Commands/EchoCommand.h"
#include "Commands/CommandCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/GetCommand.h"
#include "Commands/DelCommand.h"
#include "Commands/ExpireCommand.h"
#include "Commands/TtlCommand.h"
#include "Commands/SetexCommand.h"

#include "Respserializer.h"

#include <algorithm>
#include <cctype>

CommandDispatcher::CommandDispatcher(Store& store)
{
    handlers["PING"] = std::make_unique<PingCommand>();
    handlers["ECHO"] = std::make_unique<EchoCommand>();
    handlers["COMMAND"] = std::make_unique<CommandCommand>();

    handlers["SET"] = std::make_unique<SetCommand>(store);
    handlers["GET"] = std::make_unique<GetCommand>(store);
    handlers["DEL"] = std::make_unique<DelCommand>(store);
    handlers["EXPIRE"] = std::make_unique<ExpireCommand>(store);
    handlers["TTL"] = std::make_unique<TtlCommand>(store);
    handlers["SETEX"] = std::make_unique<SetexCommand>(store);
}

std::string CommandDispatcher::dispatch(const std::vector<std::string>& command)
{
    if (command.empty())
    {
        return RespSerializer::error("ERR empty command");
    }

    std::string commandName = command[0];

    std::transform(commandName.begin(), commandName.end(), commandName.begin(), [](unsigned char c)
    {
        return std::toupper(c);
    });

    auto it = handlers.find(commandName);

    if (it == handlers.end())
    {
        return RespSerializer::error("ERR unknown command");
    }

    return it->second->execute(command);
}