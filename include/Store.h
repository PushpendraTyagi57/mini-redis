#pragma once

#include <chrono>
#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Store
{
public:
    Store() = default;

    void setString(const std::string& key, const std::string& value);

    std::optional<std::string> getString(const std::string& key) const;

    bool deleteKey(const std::string& key);

private:
    std::unordered_map<std::string, std::string> stringStore;

    std::unordered_map<std::string, std::chrono::steady_clock::time_point> expiryStore;

    std::unordered_map<std::string, std::deque<std::string>> listStore;

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> hashStore;

    std::unordered_map<std::string, std::unordered_set<std::string>> setStore;
};