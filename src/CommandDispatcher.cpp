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
#include "Commands/HashCommands/HSetCommand.h"
#include "Commands/HashCommands/HGetCommand.h"
#include "Commands/HashCommands/HDelCommand.h"
#include "Commands/HashCommands/HGetAllCommand.h"
#include "Commands/SetCommands/SAddCommand.h"
#include "Commands/SetCommands/SRemCommand.h"
#include "Commands/SetCommands/SMembersCommand.h"
#include "Commands/SetCommands/SIsMemberCommand.h"
#include "Commands/SortedSetCommands/ZAddCommand.h"
#include "Commands/SortedSetCommands/ZRemCommand.h"
#include "Commands/SortedSetCommands/ZRevRangeCommand.h"
#include "Commands/SortedSetCommands/ZRevRankCommand.h"
#include "Commands/SortedSetCommands/ZScoreCommand.h"
#include "Commands/SortedSetCommands/ZCardCommand.h"
#include "Commands/SortedSetCommands/ZRangeCommand.h"
#include "Commands/SortedSetCommands/ZRankCommand.h"
#include "Commands/SortedSetCommands/ZCountCommand.h"
#include "Commands/SortedSetCommands/ZRangeByScoreCommand.h"
#include "Commands/SortedSetCommands/ZIncrbyCommand.h"

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

    // Hash commands
    handlers["HSET"] = std::make_unique<HSetCommand>(store);
    handlers["HGET"] = std::make_unique<HGetCommand>(store);
    handlers["HDEL"] = std::make_unique<HDelCommand>(store);
    handlers["HGETALL"] = std::make_unique<HGetAllCommand>(store);

    // Set commands
    handlers["SADD"] = std::make_unique<SAddCommand>(store);
    handlers["SREM"] = std::make_unique<SRemCommand>(store);
    handlers["SMEMBERS"] = std::make_unique<SMembersCommand>(store);
    handlers["SISMEMBER"] = std::make_unique<SIsMemberCommand>(store);

    // Sorted Set commands
    handlers["ZADD"] = std::make_unique<ZAddCommand>(store);
    handlers["ZREM"] = std::make_unique<ZRemCommand>(store);
    handlers["ZCARD"] = std::make_unique<ZCardCommand>(store);
    handlers["ZRANGE"] = std::make_unique<ZRangeCommand>(store);
    handlers["ZRANK"] = std::make_unique<ZRankCommand>(store);
    handlers["ZCOUNT"] = std::make_unique<ZCountCommand>(store);
    handlers["ZRANGEBYSCORE"] = std::make_unique<ZRangeByScoreCommand>(store);
    handlers["ZINCRBY"] = std::make_unique<ZIncrbyCommand>(store);
    handlers["ZREVRANGE"] = std::make_unique<ZRevRangeCommand>(store);
    handlers["ZREVRANK"] = std::make_unique<ZRevRankCommand>(store);
    handlers["ZSCORE"] = std::make_unique<ZScoreCommand>(store);
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