#pragma once
#include "balanced_tree.hpp"
#include "node.hpp"

template <typename K, typename V>
class RBTree : public BalancedTree<K, V> {
public:
    RBTree() {};
    ~RBTree() {
        free();
    };
    void insert(const K& key, const optional<V>& value) override;
    optional<V> search(const K& key) override;
    void remove(const K& key) override;
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2) override;
    void free();
private:
    Node<K, V>* root = nullptr;
};