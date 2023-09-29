
#pragma once
#include <string>
#include <optional>

using namespace std;

template <typename K, typename V>
class memtable {
public:
    ~memtable();
    void put(const K& key, const optional<V>& value);
    optional<V> get(const K& key);
    void remove(const K& key);
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2);
};
