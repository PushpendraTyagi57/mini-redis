#pragma once

#include "ICommand.h"
#include "Store.h"

class SetexCommand : public ICommand
{
public:
    explicit SetexCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};