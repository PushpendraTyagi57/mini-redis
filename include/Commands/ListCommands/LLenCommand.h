#pragma once

#include "ICommand.h"
#include "Store.h"

class LLenCommand : public ICommand
{
public:
    explicit LLenCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};
