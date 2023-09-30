#pragma once
#include <string>
#include <optional>
#include <vector>

using namespace std;

enum TreeType {
    RedBlackTree,
};

template <typename K, typename V>
class BalancedTree {
public:
    ~BalancedTree() {};
    virtual void insert(const K& key, const optional<V>& value) = 0;
    virtual optional<V> search(const K& key) = 0;
    virtual void remove(const K& key) = 0;
    virtual vector<pair<K, optional<V>>> scan(const K& key1, const K& key2) = 0;
};