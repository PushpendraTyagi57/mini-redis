#pragma once

#include "ICommand.h"
#include "Store.h"

class ZIncrbyCommand : public ICommand
{
public:
    explicit ZIncrbyCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};