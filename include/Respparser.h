#pragma once

#include <string>
#include <vector>
#include <stdexcept>

struct IncompleteRequest : public std::runtime_error
{
    IncompleteRequest() : std::runtime_error("Incomplete RESP request") {}
};

class RespParser
{
public:
    std::vector<std::string> parse(const std::string& request, size_t& pos);

private:
    int readInteger(const std::string& request, size_t& pos);
    std::string readBulkString(const std::string& request, size_t& pos);
    void expectCRLF(const std::string& request, size_t& pos);
};