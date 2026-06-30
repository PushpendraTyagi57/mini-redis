#include "Store.h"

#include <cstdlib>
#include <algorithm>
#include <stdexcept>

static int randomLevel()
{
    int level = 1;

    while ((std::rand() & 0xFFFF) < (0.25 * 0xFFFF) && level < MAX_LEVEL)
    {
        ++level;
    }

    return level;
}

static SkipNode* skipListInsert(SkipList& sl, const std::string& member, double score)
{
    SkipNode* update[MAX_LEVEL];
    int rank[MAX_LEVEL];

    SkipNode* x = sl.head;
    for (int i = sl.level - 1; i >= 0; --i)
    {
        rank[i] = (i == sl.level - 1) ? 0 : rank[i + 1];

        while (x->forward[i] != nullptr &&
               (x->forward[i]->score < score ||
                (x->forward[i]->score == score &&
                 x->forward[i]->member < member)))
        {
            rank[i] += x->span[i];
            x = x->forward[i];
        }
        update[i] = x;
    }

    int newLevel = randomLevel();

    if (newLevel > sl.level)
    {
        for (int i = sl.level; i < newLevel; ++i)
        {
            rank[i] = 0;
            update[i] = sl.head;
            update[i]->span[i] = sl.length;
        }
        sl.level = newLevel;
    }

    SkipNode* node = new SkipNode(newLevel, member, score);

    for (int i = 0; i < newLevel; ++i)
    {
        node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = node;

        node->span[i] = update[i]->span[i] - (rank[0] - rank[i]);
        update[i]->span[i] = (rank[0] - rank[i]) + 1;
    }

    for (int i = newLevel; i < sl.level; ++i)
    {
        ++update[i]->span[i];
    }

    node->backward = (update[0] == sl.head) ? nullptr : update[0];
    if (node->forward[0] != nullptr)
    {
        node->forward[0]->backward = node;
    }
    else
    {
        sl.tail = node;
    }

    ++sl.length;
    return node;
}

static bool skipListDelete(SkipList& sl, double score, const std::string& member, SkipNode** deletedOut = nullptr)
{
    SkipNode* update[MAX_LEVEL];
    SkipNode* x = sl.head;

    for (int i = sl.level - 1; i >= 0; --i)
    {
        while (x->forward[i] != nullptr &&
               (x->forward[i]->score < score ||
                (x->forward[i]->score == score &&
                 x->forward[i]->member < member)))
        {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];

    if (x == nullptr || x->score != score || x->member != member)
    {
        return false;
    }

    for (int i = 0; i < sl.level; ++i)
    {
        if (update[i]->forward[i] != x)
        {
            // x doesn't appear at this level — just trim the span
            update[i]->span[i] -= 1;
        }
        else
        {
            update[i]->span[i]    += x->span[i] - 1;
            update[i]->forward[i]  = x->forward[i];
        }
    }

    if (x->forward[0] != nullptr)
    {
        x->forward[0]->backward = x->backward;
    }
    else
    {
        sl.tail = x->backward;
    }

    while (sl.level > 1 && sl.head->forward[sl.level - 1] == nullptr)
    {
        --sl.level;
    }

    --sl.length;

    if (deletedOut)
    {
        *deletedOut = x;
    }
    else
    {
        delete x;
    }

    return true;
}

static SkipNode* skipListSearch(const SkipList& sl, const std::string& member, double score)
{
    SkipNode* x = sl.head;
    for (int i = sl.level - 1; i >= 0; --i)
    {
        while (x->forward[i] != nullptr &&
               (x->forward[i]->score < score ||
                (x->forward[i]->score == score &&
                 x->forward[i]->member < member)))
        {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != nullptr && x->score == score && x->member == member)
    {
        return x;
    }
    return nullptr;
}

int Store::zadd(const std::string& key, double score, const std::string& member)
{
    SortedSet& zs = sortedSetStore[key];

    auto it = zs.memberToScore.find(member);
    if (it != zs.memberToScore.end())
    {
        double oldScore = it->second;
        if (oldScore == score)
        {
            return 0;
        }

        skipListDelete(zs.skipList, oldScore, member);
        zs.memberToScore[member] = score;
        SkipNode* node = skipListInsert(zs.skipList, member, score);
        zs.memberToNode[member] = node;
        return 0;
    }

    SkipNode* node = skipListInsert(zs.skipList, member, score);
    zs.memberToScore[member]  = score;
    zs.memberToNode[member]   = node;
    return 1;
}

std::optional<double> Store::zscore(const std::string& key, const std::string& member) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return std::nullopt;

    const SortedSet& zs = kit->second;
    auto it = zs.memberToScore.find(member);
    if (it == zs.memberToScore.end())
    {
        return std::nullopt;
    }

    return it->second;
}

int Store::zrem(const std::string& key, const std::string& member)
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return 0;

    SortedSet& zs = kit->second;
    auto it = zs.memberToScore.find(member);
    if (it == zs.memberToScore.end())
    {
        return 0;
    }

    double score = it->second;
    skipListDelete(zs.skipList, score, member);
    zs.memberToScore.erase(member);
    zs.memberToNode.erase(member);

    if (zs.memberToScore.empty())
    {
        sortedSetStore.erase(kit);
    }

    return 1;
}

double Store::zincrby(const std::string& key, double increment, const std::string& member)
{
    SortedSet& zs = sortedSetStore[key];

    auto it = zs.memberToScore.find(member);
    if (it == zs.memberToScore.end())
    {
        SkipNode* node = skipListInsert(zs.skipList, member, increment);
        zs.memberToScore[member] = increment;
        zs.memberToNode[member]  = node;
        return increment;
    }

    double oldScore = it->second;
    double newScore = oldScore + increment;

    skipListDelete(zs.skipList, oldScore, member);
    SkipNode* node = skipListInsert(zs.skipList, member, newScore);
    zs.memberToScore[member] = newScore;
    zs.memberToNode[member]  = node;
    return newScore;
}

int Store::zcard(const std::string& key) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
    {
        return 0;
    }
    return kit->second.skipList.length;
}

int Store::zcount(const std::string& key, double minScore, double maxScore) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
    {
        return 0;
    }

    const SkipList& sl = kit->second.skipList;
    int count = 0;

    SkipNode* x = sl.head;
    for (int i = sl.level - 1; i >= 0; --i)
    {
        while (x->forward[i] != nullptr && x->forward[i]->score < minScore)
            x = x->forward[i];
    }

    x = x->forward[0];

    while (x != nullptr && x->score <= maxScore)
    {
        ++count;
        x = x->forward[0];
    }
    return count;
}

static std::vector<std::pair<std::string, double>> rangeByRank(const SkipList& sl, int start, int stop)
{
    int len = sl.length;
    if (len == 0)
    {
        return {};
    }

    if (start < 0) start = std::max(0, len + start);
    if (stop  < 0) stop  = len + stop;
    if (stop >= len) stop = len - 1;
    if (start > stop) return {};

    SkipNode* x = sl.head;
    int traversed = 0;
    for (int i = sl.level - 1; i >= 0; --i)
    {
        while (x->forward[i] != nullptr &&
               traversed + x->span[i] <= start)
        {
            traversed += x->span[i];
            x = x->forward[i];
        }
    }
    x = x->forward[0];

    std::vector<std::pair<std::string, double>> result;
    result.reserve(stop - start + 1);
    for (int i = start; i <= stop && x != nullptr; ++i, x = x->forward[0])
        result.emplace_back(x->member, x->score);

    return result;
}

std::vector<std::pair<std::string, double>>
Store::zrange(const std::string& key, int start, int stop) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return {};
    return rangeByRank(kit->second.skipList, start, stop);
}

std::vector<std::pair<std::string, double>>
Store::zrevrange(const std::string& key, int start, int stop) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return {};

    const SkipList& sl  = kit->second.skipList;
    int len = sl.length;

    if (len == 0)
        return {};

    int fwdStart = len - 1 - (stop  < 0 ? len + stop  : stop);
    int fwdStop = len - 1 - (start < 0 ? len + start : start);

    auto fwd = rangeByRank(sl, fwdStart, fwdStop);
    std::reverse(fwd.begin(), fwd.end());
    return fwd;
}

std::vector<std::pair<std::string, double>>
Store::zrangebyscore(const std::string& key, double minScore, double maxScore) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return {};

    const SkipList& sl = kit->second.skipList;

    SkipNode* x = sl.head;
    for (int i = sl.level - 1; i >= 0; --i)
        while (x->forward[i] != nullptr && x->forward[i]->score < minScore)
            x = x->forward[i];

    x = x->forward[0];

    std::vector<std::pair<std::string, double>> result;
    while (x != nullptr && x->score <= maxScore)
    {
        result.emplace_back(x->member, x->score);
        x = x->forward[0];
    }
    return result;
}

static int skipListGetRank(const SkipList& sl, double score, const std::string& member)
{
    int rank = 0;
    const SkipNode* x = sl.head;

    for (int i = sl.level - 1; i >= 0; --i)
    {
        while (x->forward[i] != nullptr &&
               (x->forward[i]->score < score ||
                (x->forward[i]->score == score &&
                 x->forward[i]->member <= member)))
        {
            rank += x->span[i];
            x = x->forward[i];
        }
        if (x != sl.head && x->score == score && x->member == member)
            return rank - 1;
    }

    if (x != sl.head && x->score == score && x->member == member)
        return rank - 1;

    return -1;
}

std::optional<int> Store::zrank(const std::string& key, const std::string& member) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
    {
        return std::nullopt;
    }

    const SortedSet& zs = kit->second;
    auto it = zs.memberToScore.find(member);
    if (it == zs.memberToScore.end())
        return std::nullopt;

    int r = skipListGetRank(zs.skipList, it->second, member);
    if (r < 0)
    {
        return std::nullopt;
    }

    return r;
}

std::optional<int> Store::zrevrank(const std::string& key, const std::string& member) const
{
    auto kit = sortedSetStore.find(key);
    if (kit == sortedSetStore.end())
        return std::nullopt;

    const SortedSet& zs = kit->second;
    auto it = zs.memberToScore.find(member);
    if (it == zs.memberToScore.end())
        return std::nullopt;

    int r = skipListGetRank(zs.skipList, it->second, member);
    if (r < 0)
        return std::nullopt;

    return zs.skipList.length - 1 - r;
}