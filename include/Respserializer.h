#pragma once

#include <string>

class RespSerializer
{
public:
    std::string simpleString(const std::string& value);
    std::string bulkString(const std::string& value);
    std::string integer(long long value);
    std::string error(const std::string& message);
    std::string nullBulkString();
    std::string emptyArray();
}