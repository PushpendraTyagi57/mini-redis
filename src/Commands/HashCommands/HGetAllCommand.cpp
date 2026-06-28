#include "Commands/HashCommands/HGetAllCommand.h"
#include "Respserializer.h"

HGetAllCommand::HGetAllCommand(Store& store) : store(store)
{
}

std::string HGetAllCommand::execute(const std::vector<std::string>& command)
{
    if (command.size() != 2)
    {
        return RespSerializer::error("ERR wrong number of arguments for 'hgetall' command");
    }

    const std::string& key = command[1];

    auto fields = store.hgetall(key);

    std::vector<std::string> response;

    for (const auto& [field, value] : fields)
    {
        response.push_back(field);
        response.push_back(value);
    }

    return RespSerializer::array(response);
}