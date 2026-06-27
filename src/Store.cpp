#include "Store.h"

void Store::setString(const std::string& key, const std::string& value)
{
    stringStore[key] = value;
}

std::optional<std::string> Store::getString(const std::string& key)
{
    removeExpired();

    auto it = stringStore.find(key);

    if (it == stringStore.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool Store::deleteKey(const std::string& key)
{
    removeExpired();

    auto it = stringStore.find(key);

    if (it == stringStore.end())
    {
        return false;
    }

    stringStore.erase(it);

    expiryStore.erase(key);

    return true;
}

bool Store::expireKey(const std::string& key, std::chrono::seconds ttl)
{
    removeExpired();

    if (stringStore.find(key) == stringStore.end())
    {
        return false;
    }

    auto now = std::chrono::steady_clock::now();
    expiryStore[key] = now + ttl;

    return true;
}

std::optional<std::chrono::seconds> Store::getTtl(const std::string& key) const
{
    auto it = expiryStore.find(key);

    if (it == expiryStore.end())
    {
        return std::nullopt;
    }

    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(it->second - now);

    if (remaining <= std::chrono::seconds::zero())
    {
        return std::nullopt;
    }

    return remaining;
}

bool Store::isExpired(const std::string& key) const
{
    auto it = expiryStore.find(key);

    if (it == expiryStore.end())
    {
        return false;
    }

    auto now = std::chrono::steady_clock::now();

    return now >= it->second;
}

void Store::removeExpired()
{
    auto now = std::chrono::steady_clock::now();

    for (auto it = expiryStore.begin(); it != expiryStore.end();)
    {
        if (now >= it->second)
        {
            stringStore.erase(it->first);
            listStore.erase(it->first);
            hashStore.erase(it->first);
            setStore.erase(it->first);
            it = expiryStore.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Store::setex(const std::string& key, std::chrono::seconds ttl, const std::string& value)
{
    setString(key, value);
    expireKey(key, ttl);
}

void Store::lpush(const std::string& key, const std::string& value)
{
    listStore[key].push_front(value);
}

void Store::rpush(const std::string& key, const std::string& value)
{
    listStore[key].push_back(value);
}

std::optional<std::string> Store::lpop(const std::string& key)
{
    auto it = listStore.find(key);

    if (it == listStore.end() || it->second.empty())
    {
        return std::nullopt;
    }

    std::string value = it->second.front();
    it->second.pop_front();

    return value;
}

std::optional<std::string> Store::rpop(const std::string& key)
{
    auto it = listStore.find(key);

    if (it == listStore.end() || it->second.empty())
    {
        return std::nullopt;
    }

    std::string value = it->second.back();
    it->second.pop_back();

    return value;
}

ssize_t Store::llen(const std::string& key) const
{
    auto it = listStore.find(key);

    if (it == listStore.end())
    {
        return 0;
    }

    return it->second.size();
}

std::vector<std::string> Store::lrange(const std::string& key, ssize_t start, ssize_t stop) const
{
    std::vector<std::string> result;

    auto it = listStore.find(key);

    if (it == listStore.end())
    {
        return result;
    }

    const auto& list = it->second;
    ssize_t listSize = static_cast<ssize_t>(list.size());

    if (start < 0)
    {
        start = std::max(listSize + start, static_cast<ssize_t>(0));
    }
    else
    {
        start = std::min(start, listSize);
    }

    if (stop < 0)
    {
        stop = std::max(listSize + stop, static_cast<ssize_t>(-1));
    }
    else
    {
        stop = std::min(stop, listSize - 1);
    }

    for (ssize_t i = start; i <= stop; ++i)
    {
        result.push_back(list[i]);
    }

    return result;
}