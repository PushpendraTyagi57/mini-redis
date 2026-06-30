#pragma once

#include "ICommand.h"
#include "Store.h"

class ZCountCommand : public ICommand
{
public:
    explicit ZCountCommand(Store& store);
    
    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};