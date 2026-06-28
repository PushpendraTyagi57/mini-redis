#pragma once

#include "ICommand.h"
#include "Store.h"

class HSetCommand : public ICommand
{
public:
    explicit HSetCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};