#pragma once

#include "Store.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ICommand.h"

class CommandDispatcher
{
public:
    explicit CommandDispatcher(Store& store);

    std::string dispatch(const std::vector<std::string>& command);

private:
    std::unordered_map<std::string, std::unique_ptr<ICommand>> handlers;
};