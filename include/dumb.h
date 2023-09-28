#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

template <typename K, typename V>
class DumbDB {
public:
    void Open(const std::string& database_name);
    void Put(const K& key, const V& value);
    V Get(const K& key);
    std::vector<std::pair<K, V>> Scan(const K& key1, const K& key2);
    void Close();

private:
    std::unordered_map<K, V> db_;
};