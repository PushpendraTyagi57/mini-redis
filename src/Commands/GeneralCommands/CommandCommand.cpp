#include "Commands/GeneralCommands/CommandCommand.h"
#include "Respserializer.h"

std::string CommandCommand::execute(const std::vector<std::string>& command)
{
    return RespSerializer::emptyArray();
}