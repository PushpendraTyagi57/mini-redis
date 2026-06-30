#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRevRangeCommand : public ICommand
{
public:
    explicit ZRevRangeCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};