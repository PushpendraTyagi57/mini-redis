#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRankCommand : public ICommand
{
public:
    explicit ZRankCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};