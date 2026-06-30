#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRangeCommand : public ICommand
{
public:
    explicit ZRangeCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};