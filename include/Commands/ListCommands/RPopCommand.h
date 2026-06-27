#pragma once

#include "ICommand.h"
#include "Store.h"

class RPopCommand : public ICommand
{
public:
    explicit RPopCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};
