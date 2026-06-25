#include "Respserializer.h"

std::string RespSerializer::simpleString(const std::string& value)
{
    return "+" + value + "\r\n";
}

std::string RespSerializer::bulkString(const std::string& value)
{
    return "$" + std::to_string(value.length()) + "\r\n" + value + "\r\n";
}

std::string RespSerializer::integer(long long value)
{
    return ":" + std::to_string(value) + "\r\n";
}

std::string RespSerializer::error(const std::string& message)
{
    return "-" + message + "\r\n";
}

std::string RespSerializer::nullBulkString()
{
    return "$-1\r\n";
}

std::string RespSerializer::emptyArray()
{
    return "*0\r\n";
}