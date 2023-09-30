#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <optional>

using namespace std;

template <typename K, typename V>
class IDumbDB {
public:
    virtual ~IDumbDB() {};
    virtual void Open(const string& database_name) = 0;
    virtual void Put(const K& key, const optional<V>& value) = 0;
    virtual optional<V> Get(const K& key) = 0;
    virtual void Delete(const K& key) = 0;
    virtual vector<pair<K, optional<V>>> Scan(const K& key1, const K& key2) = 0;
    virtual void Close() = 0;
};

template <typename K, typename V>
IDumbDB<K, V>* CreateDumbDB();
