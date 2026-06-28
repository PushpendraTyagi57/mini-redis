#pragma once

#include "ICommand.h"
#include "Store.h"

class HGetCommand : public ICommand
{
public:
    explicit HGetCommand(Store& store);
    std::string execute(const std::vector<std::string>& command) override;
    
private:
    Store& store;
};