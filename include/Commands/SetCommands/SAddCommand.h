#pragma once

#include "ICommand.h"
#include "Store.h"

class SAddCommand : public ICommand
{
public:
    explicit SAddCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};