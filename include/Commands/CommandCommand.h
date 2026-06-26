#pragma once

#include "ICommand.h"

class CommandCommand : public ICommand
{
public:
    std::string execute(const std::vector<std::string>& command) override;
};