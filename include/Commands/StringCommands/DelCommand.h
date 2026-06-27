#pragma once

#include "ICommand.h"
#include "Store.h"

class DelCommand : public ICommand
{
public:
    explicit DelCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};