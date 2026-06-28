#pragma once

#include <chrono>
#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Store
{
public:
    Store() = default;

    //-- String operations
    void setString(const std::string& key, const std::string& value);

    std::optional<std::string> getString(const std::string& key);

    bool deleteKey(const std::string& key);

    bool expireKey(const std::string& key, std::chrono::seconds ttl);

    std::optional<std::chrono::seconds> getTtl(const std::string& key) const;

    bool isExpired(const std::string& key) const;

    void removeExpired();

    void setex(const std::string& key, std::chrono::seconds ttl, const std::string& value);

    //-- List operations
    void lpush(const std::string& key, const std::string& value);
    void rpush(const std::string& key, const std::string& value);

    std::optional<std::string> lpop(const std::string& key);
    std::optional<std::string> rpop(const std::string& key);

    ssize_t llen(const std::string& key) const;

    std::vector<std::string> lrange(const std::string& key, ssize_t start, ssize_t stop) const;

    //-- Hash operations
    bool hset(const std::string& key, const std::string& field, const std::string& value);
    std::optional<std::string> hget(const std::string& key, const std::string& field) const;
    std::unordered_map<std::string, std::string> hgetall(const std::string& key) const;
    bool hdel(const std::string& key, const std::string& field);

    //-- Set operations
    bool sadd(const std::string& key, const std::string& member);
    bool srem(const std::string& key, const std::string& member);
    bool sismember(const std::string& key, const std::string& member);
    std::unordered_set<std::string> smembers(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> stringStore;

    std::unordered_map<std::string, std::chrono::steady_clock::time_point> expiryStore;

    std::unordered_map<std::string, std::deque<std::string>> listStore;

    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> hashStore;

    std::unordered_map<std::string, std::unordered_set<std::string>> setStore;
};