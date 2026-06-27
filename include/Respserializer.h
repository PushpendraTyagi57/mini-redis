#pragma once

#include <string>
#include <vector>

class RespSerializer
{
public:
    static std::string simpleString(const std::string& value);
    static std::string bulkString(const std::string& value);
    static std::string integer(long long value);
    static std::string error(const std::string& message);
    static std::string nullBulkString();
    static std::string emptyArray();
    static std::string array(const std::vector<std::string>& elements);
};