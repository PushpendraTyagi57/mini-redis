#pragma once

#include "ICommand.h"
#include "Store.h"

class SIsMemberCommand : public ICommand
{
public:
    explicit SIsMemberCommand(Store& store);

    std::string execute(const std::vector<std::string>& command) override;

private:
    Store& store;
};