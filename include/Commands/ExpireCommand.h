#pragma once

#include "ICommand.h"
#include "Store.h"

class ExpireCommand : public ICommand
{
public:
    explicit ExpireCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};