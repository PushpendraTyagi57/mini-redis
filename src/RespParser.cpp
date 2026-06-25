#include "Respparser.h"

#include <stdexcept>

std::vector<std::string> Respparser::parse(const std::string& request)
{
    size_t pos = 0;
    if (request.empty() || request[pos] != '*')
    {
        throw std::runtime_error("Expected RESP array");
    }
    
    pos++;

    int numberOfElements = readInteger(request, pos);

    std::vector<std::string> result;
    result.reserve(numberOfElements);

    for (int i = 0; i < numberOfElements; i++)
    {
        result.push_back(readBulkString(request, pos));
    }

    return result;
}

int Respparser::readInteger(const std::string& request, size_t& pos)
{
    int value = 0;

    while (pos < request.size() && request[pos] != '\r')
    {
        if (!std::isdigit(request[pos]))
        {
            throw std::runtime_error("Invalid Integer");
        }

        value = value * 10 + (request[pos] - '0');
        pos++;
    }

    expectCRLF(request, pos);

    return value;
}

std::string Respparser::readBulkString(const std::string& request, size_t& pos)
{
    if (pos >= request.size() || request[pos] != '$')
    {
        throw std::runtime_error("Expected bulk string");
    }

    pos++;

    int length = readInteger(request, pos);

    if (pos + length > request.size())
    {
        throw std::runtime_error("Bulk string too short");
    }

    std::string value = request.substr(pos, length);

    pos += length;

    expect CRLF(request, pos);

    return value;
}

void Respparser::expectCRLF(const std::string& request, size_t& pos)
{
    if (pos + 1 >= request.size())
    {
        throw std::runtime_error("Unexpected end of request");
    }

    if (request[pos] != '\r' || request[pos + 1] != '\n')
    {
        throw std::runtime_error("Expected CRLF");
    }

    pos += 2;
}