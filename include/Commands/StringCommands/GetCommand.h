#pragma once

#include "ICommand.h"
#include "Store.h"

class GetCommand : public ICommand
{
public:
    explicit GetCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};