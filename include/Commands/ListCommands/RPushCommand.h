#pragma once

#include "ICommand.h"
#include "Store.h"

class RPushCommand : public ICommand
{
public:
    explicit RPushCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};