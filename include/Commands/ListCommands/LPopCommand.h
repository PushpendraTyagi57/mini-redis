#pragma once

#include "ICommand.h"
#include "Store.h"

class LPopCommand : public ICommand
{
public:
    explicit LPopCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};