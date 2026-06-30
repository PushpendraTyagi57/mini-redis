#pragma once

#include "ICommand.h"
#include "Store.h"

class ZScoreCommand : public ICommand
{
public:
    explicit ZScoreCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};