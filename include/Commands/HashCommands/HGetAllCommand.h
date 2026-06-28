#pragma once

#include "ICommand.h"
#include "Store.h"

class HGetAllCommand : public ICommand
{
public:
    explicit HGetAllCommand(Store& store);
    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};