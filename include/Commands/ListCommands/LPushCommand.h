#pragma once

#include "ICommand.h"
#include "Store.h"

class LPushCommand : public ICommand
{
public:
    explicit LPushCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};