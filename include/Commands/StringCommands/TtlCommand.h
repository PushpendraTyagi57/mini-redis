#pragma once

#include "ICommand.h"
#include "Store.h"

class TtlCommand : public ICommand
{
public:
    explicit TtlCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};