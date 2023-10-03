#pragma once
#include <string>
#include <optional>
#include <vector>

#define FILE_PATH "./data/"

using namespace std;

template <typename K, typename V>
class Storage {
public:
    Storage();
    ~Storage();
    void put(const K& key, const optional<V>& value);
    optional<V> get(const K& key);
    void remove(const K& key);
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2);
    void open(const string& database_name);
private:
    string database_name_;
};