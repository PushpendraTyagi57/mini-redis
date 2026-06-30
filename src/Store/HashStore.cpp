#include "Store.h"

bool Store::hset(const std::string& key, const std::string& field, const std::string& value)
{
    auto& hash = hashStore[key];

    auto it = hash.find(field);

    if (it == hash.end())
    {
        hash[field] = value;
        return true;
    }

    it->second = value;
    return false;
}

std::optional<std::string> Store::hget(const std::string& key, const std::string& field) const
{
    auto it = hashStore.find(key);

    if (it == hashStore.end())
    {
        return std::nullopt;
    }

    const auto& hash = it->second;
    auto fieldIt = hash.find(field);

    if (fieldIt == hash.end())
    {
        return std::nullopt;
    }

    return fieldIt->second;
}

std::unordered_map<std::string, std::string> Store::hgetall(const std::string& key) const
{
    auto it = hashStore.find(key);

    if (it == hashStore.end())
    {
        return {};
    }

    return it->second;
}

bool Store::hdel(const std::string& key, const std::string& field)
{
    auto it = hashStore.find(key);

    if (it == hashStore.end())
    {
        return false;
    }

    auto& hash = it->second;
    auto fieldIt = hash.find(field);

    if (fieldIt == hash.end())
    {
        return false;
    }

    hash.erase(fieldIt);

    if (hash.empty())
    {
        hashStore.erase(it);
    }

    return true;
}