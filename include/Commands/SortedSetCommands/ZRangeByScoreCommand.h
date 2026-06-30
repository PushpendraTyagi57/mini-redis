#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRangeByScoreCommand : public ICommand
{
public:
    explicit ZRangeByScoreCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};

