#include "CommandDispatcher.h"

#include "Commands/GeneralCommands/PingCommand.h"
#include "Commands/GeneralCommands/EchoCommand.h"
#include "Commands/GeneralCommands/CommandCommand.h"
#include "Commands/StringCommands/SetCommand.h"
#include "Commands/StringCommands/GetCommand.h"
#include "Commands/StringCommands/DelCommand.h"
#include "Commands/StringCommands/ExpireCommand.h"
#include "Commands/StringCommands/TtlCommand.h"
#include "Commands/StringCommands/SetexCommand.h"
#include "Commands/ListCommands/LPushCommand.h"
#include "Commands/ListCommands/RPushCommand.h"
#include "Commands/ListCommands/LPopCommand.h"
#include "Commands/ListCommands/RPopCommand.h"
#include "Commands/ListCommands/LLenCommand.h"
#include "Commands/ListCommands/LRangeCommand.h"

#include "Respserializer.h"

#include <algorithm>
#include <cctype>

CommandDispatcher::CommandDispatcher(Store& store)
{
    // General commands
    handlers["PING"] = std::make_unique<PingCommand>();
    handlers["ECHO"] = std::make_unique<EchoCommand>();
    handlers["COMMAND"] = std::make_unique<CommandCommand>();

    // String commands
    handlers["SET"] = std::make_unique<SetCommand>(store);
    handlers["GET"] = std::make_unique<GetCommand>(store);
    handlers["DEL"] = std::make_unique<DelCommand>(store);
    handlers["EXPIRE"] = std::make_unique<ExpireCommand>(store);
    handlers["TTL"] = std::make_unique<TtlCommand>(store);
    handlers["SETEX"] = std::make_unique<SetexCommand>(store);

    // List commands
    handlers["LPUSH"] = std::make_unique<LPushCommand>(store);
    handlers["RPUSH"] = std::make_unique<RPushCommand>(store);
    handlers["LPOP"] = std::make_unique<LPopCommand>(store);
    handlers["RPOP"] = std::make_unique<RPopCommand>(store);
    handlers["LLEN"] = std::make_unique<LLenCommand>(store);
    handlers["LRANGE"] = std::make_unique<LRangeCommand>(store);
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