#pragma once

#include <string>
#include <vector>

class RespParser
{
public:
    std::vector<std::string> parse(const std::string& request);

private:
    int readInteger(const std::string& request, size_t& pos);
    std::string readBulkString(const std::string& request, size_t& pos);
    void expectCRLF(const std::string& request, size_t& pos);
};