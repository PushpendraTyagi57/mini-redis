#pragma once

#include "ICommand.h"
#include "Store.h"

class SetCommand : public ICommand
{
public:
    explicit SetCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};