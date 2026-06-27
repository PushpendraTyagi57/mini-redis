#pragma once

#include "ICommand.h"

class EchoCommand : public ICommand
{
public:
    std::string execute(const std::vector<std::string>& command) override;
};