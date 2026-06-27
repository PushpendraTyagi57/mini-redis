#include "Commands/TtlCommand.h"

#include "Respserializer.h"

TtlCommand::TtlCommand(Store& store)
    : store(store)
{
}

std::string TtlCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error(
            "ERR wrong number of arguments for 'ttl' command");
    }

    auto ttl = store.getTtl(command[1]);

    if (!ttl.has_value())
    {
        return RespSerializer::integer(-1);
    }

    return RespSerializer::integer(ttl->count());
}