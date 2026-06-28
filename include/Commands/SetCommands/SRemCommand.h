#pragma once

#include "ICommand.h"
#include "Store.h"

class SRemCommand : public ICommand
{
public:
    explicit SRemCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};