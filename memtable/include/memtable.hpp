
#pragma once
#include <string>
#include <optional>
#include "balanced_tree_factory.hpp"
#include "config.hpp"

using namespace std;

template <typename K, typename V>
class Memtable {
public:
    Memtable();
    ~Memtable();
    void put(const K& key, const optional<V>& value);
    optional<V> get(const K& key);
    void remove(const K& key);
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2);
    bool has_key(const K& key);
    void flush_to_storage();
private:
    shared_ptr<BalancedTree<K, V>> tree;
};
