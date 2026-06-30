#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRevRankCommand : public ICommand
{
public:
    explicit ZRevRankCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};