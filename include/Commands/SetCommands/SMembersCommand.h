#pragma once

#include "ICommand.h"
#include "Store.h"

class SMembersCommand : public ICommand
{
public:
    explicit SMembersCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};