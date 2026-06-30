#pragma once

#include "ICommand.h"
#include "Store.h"

class ZAddCommand : public ICommand
{
public:
    explicit ZAddCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};