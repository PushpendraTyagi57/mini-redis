# Mini Redis

A Redis-inspired in-memory key-value database written in modern C++17 from scratch.

The project implements the Redis Serialization Protocol (RESP), a custom TCP server using Linux sockets, command dispatching, multiple Redis data structures, key expiration, skip-list backed sorted sets, and an event-driven networking model using `epoll`.

## Features

### Networking
- Custom TCP server built with POSIX sockets
- Non-blocking I/O
- Event-driven architecture using Linux `epoll`
- Handles multiple concurrent client connections
- Compatible with `redis-cli`

### RESP Protocol
- RESP2 parser
- RESP response serializer
- Array parsing
- Bulk Strings
- Integers
- Simple Strings
- Null responses

### Supported Commands

#### General
- PING
- ECHO
- COMMAND

#### Strings
- SET
- GET
- DEL
- EXPIRE
- TTL
- SETEX

#### Lists
- LPUSH
- RPUSH
- LPOP
- RPOP
- LLEN
- LRANGE

#### Hashes
- HSET
- HGET
- HGETALL
- HDEL

#### Sets
- SADD
- SREM
- SMEMBERS
- SISMEMBER

#### Sorted Sets
- ZADD
- ZREM
- ZSCORE
- ZCARD
- ZCOUNT
- ZRANGE
- ZREVRANGE
- ZRANGEBYSCORE
- ZRANK
- ZREVRANK
- ZINCRBY

---

## Architecture

```
                redis-cli
                     │
                     │ RESP
                     ▼
             TCP Server (epoll)
                     │
                     ▼
              RESP Parser
                     │
                     ▼
          Command Dispatcher
                     │
    ┌────────────────┼────────────────┐
    ▼                ▼                ▼
 String         List/Hash/Set     Sorted Set
  Store            Stores         (Skip List)
                     │
                     ▼
              RESP Serializer
                     │
                     ▼
                 Client
```

---

## Project Structure

```
mini-redis
├── include
│   ├── Commands
│   │   ├── GeneralCommands
│   │   ├── StringCommands
│   │   ├── ListCommands
│   │   ├── HashCommands
│   │   ├── SetCommands
│   │   └── SortedSetCommands
│   ├── CommandDispatcher.h
│   ├── ICommand.h
│   ├── Respparser.h
│   ├── Respserializer.h
│   ├── Store.h
│   └── Tcpserver.h
│
├── src
│   ├── Commands
│   │   ├── GeneralCommands
│   │   ├── StringCommands
│   │   ├── ListCommands
│   │   ├── HashCommands
│   │   ├── SetCommands
│   │   └── SortedSetCommands
│   │
│   ├── Store
│   │   ├── Store.cpp
│   │   ├── StringStore.cpp
│   │   ├── ListStore.cpp
│   │   ├── HashStore.cpp
│   │   ├── SetStore.cpp
│   │   └── SortedSetStore.cpp
│   │
│   ├── CommandDispatcher.cpp
│   ├── Respparser.cpp
│   ├── Respserializer.cpp
│   ├── Tcpserver.cpp
│   └── main.cpp
│
├── CMakeLists.txt
├── README.md
└── build/

```

---

## Data Structures

| Redis Type | Internal Structure |
|------------|-------------------|
| String | unordered_map |
| List | deque |
| Hash | unordered_map<string, unordered_map> |
| Set | unordered_set |
| Sorted Set | Skip List + unordered_map |

---

## Performance

Benchmark performed using:

```bash
redis-benchmark -p 6379 -t set,get -c 100 -n 100000
```

Results:

```
Throughput

86,132 requests/sec

Latency

Average : 1.127 ms
P50     : 0.999 ms
P95     : 2.079 ms
P99     : 2.999 ms
Maximum : 8.623 ms
```

---

## Build

Requirements

- Linux
- CMake
- GCC / Clang
- C++17

Clone

```bash
git clone https://github.com/PushpendraTyagi57/mini-redis.git
cd mini-redis
```

Build

```bash
mkdir build
cd build

cmake ..
make
```

Run

```bash
./MiniRedis
```

---

## Usage

Connect using Redis CLI

```bash
redis-cli -p 6379
```

Example

```redis
SET name Pushpendra
GET name

LPUSH nums 1
LPUSH nums 2
LRANGE nums 0 -1

HSET user name Pushpendra
HGETALL user

SADD fruits apple
SMEMBERS fruits

ZADD leaderboard 100 Pushpendra
ZRANGE leaderboard 0 -1 WITHSCORES
```

---

## Design Highlights

- Modular command architecture using the Command Pattern
- Separate storage engine implementation for each Redis data type
- Skip-list implementation for efficient sorted sets
- RESP protocol implemented from scratch
- Event-driven networking using `epoll`
- Non-blocking socket communication
- Clean separation between networking, parsing, command execution, and storage

---

## Future Improvements

- Transactions (`MULTI`, `EXEC`)
- Publish / Subscribe
- RDB snapshots
- Append Only File (AOF)
- Memory eviction policies
- Authentication
- Replication
- Cluster support

---

## Tech Stack

- C++17
- POSIX Sockets
- epoll
- CMake
- STL

---

## License

This project is intended for educational purposes and systems programming practice.