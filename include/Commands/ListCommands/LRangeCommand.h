#pragma once

#include "ICommand.h"
#include "Store.h"

class LRangeCommand : public ICommand
{
public:
    explicit LRangeCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};
