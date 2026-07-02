#include "Respparser.h"

std::vector<std::string> RespParser::parse(const std::string& request, size_t& pos)
{
    if (pos >= request.size())
    {
        throw IncompleteRequest();
    }

    if (request[pos] != '*')
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

int RespParser::readInteger(const std::string& request, size_t& pos)
{
    int value = 0;

    while (true)
    {
        if (pos >= request.size())
        {
            throw IncompleteRequest();
        }

        if (request[pos] == '\r')
        {
            break;
        }

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

std::string RespParser::readBulkString(const std::string& request, size_t& pos)
{
    if (pos >= request.size())
    {
        throw IncompleteRequest();
    }

    if (request[pos] != '$')
    {
        throw std::runtime_error("Expected bulk string");
    }

    pos++;

    int length = readInteger(request, pos);

    if (pos + length + 2 > request.size())
    {
        throw IncompleteRequest();
    }

    std::string value = request.substr(pos, length);
    pos += length;

    expectCRLF(request, pos);
    return value;
}

void RespParser::expectCRLF(const std::string& request, size_t& pos)
{
    if (pos + 1 >= request.size())
    {
        throw IncompleteRequest();
    }

    if (request[pos] != '\r' || request[pos + 1] != '\n')
    {
        throw std::runtime_error("Expected CRLF");
    }

    pos += 2;
}