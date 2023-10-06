#pragma once
#include <string>
#include <optional>
#include <vector>

using namespace std;

template <typename K, typename V> // alt
class Storage {
public:
    Storage();
    Storage(string database_path);
    ~Storage();
    void put();
    optional<V> get(const K& key);
    void remove(const K& key);
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2);
    void update();
    int get_sst_num();
private:
    vector<int> sst_list;
    int sst_num;
    string database_path;
};