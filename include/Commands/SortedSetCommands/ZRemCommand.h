#pragma once

#include "ICommand.h"
#include "Store.h"

class ZRemCommand : public ICommand
{
public:
    explicit ZRemCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};