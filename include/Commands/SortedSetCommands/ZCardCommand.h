#pragma once

#include "ICommand.h"
#include "Store.h"

class ZCardCommand : public ICommand
{
public:
    explicit ZCardCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};