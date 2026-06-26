#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ICommand.h"

class CommandDispatcher
{
public:
    CommandDispatcher();

    std::string dispatch(const std::vector<std::string>& command);

private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> handlers;
};