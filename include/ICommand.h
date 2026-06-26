#pragma once

#include <string>
#include <vector>

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual std::string execute(const std::vector<std::string>& command) = 0;
};