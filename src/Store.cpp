#include "Store.h"

void Store::setString(const std::string& key,
                const std::string& value)
{
    stringStore[key] = value;
}

std::optional<std::string> Store::getString(const std::string& key) const
{
    auto it = stringStore.find(key);

    if (it == stringStore.end())
    {
        return std::nullopt;
    }

    return it->second;
}

bool Store::deleteKey(const std::string& key)
{
    auto it = stringStore.find(key);

    if (it == stringStore.end())
    {
        return false;
    }

    stringStore.erase(it);

    expiryStore.erase(key);

    return true;
}