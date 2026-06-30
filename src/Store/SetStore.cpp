#include "Store.h"

bool Store::sadd(const std::string& key, const std::string& member)
{
    auto& set = setStore[key];

    auto result = set.insert(member);

    return result.second;
}

bool Store::srem(const std::string& key, const std::string& member)
{
    auto it = setStore.find(key);

    if (it == setStore.end())
    {
        return false;
    }

    auto& set = it->second;
 
    auto memberIt = set.find(member);
    
    if (memberIt == set.end())
    {
        return false;
    }

    set.erase(memberIt);

    if (set.empty())
    {
        setStore.erase(it);
    }

    return true;
}

bool Store::sismember(const std::string& key, const std::string& member)
{
    auto it = setStore.find(key);

    if (it == setStore.end())
    {
        return false;
    }

    const auto& set = it->second;
    return set.find(member) != set.end();
}

std::unordered_set<std::string> Store::smembers(const std::string& key) const
{
    auto it = setStore.find(key);

    if (it == setStore.end())
    {
        return {};
    }

    return it->second;
}