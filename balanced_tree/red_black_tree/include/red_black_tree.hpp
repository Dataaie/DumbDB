#pragma once
#include "balanced_tree.hpp"
#include "node.hpp"


/*
    1. A red node does not have a red child.
    2.Every path from a given node to any of its descendant NIL nodes goes through the same number of black nodes.
*/

template <typename K, typename V>
class RBTree : public BalancedTree<K, V> {
public:
    RBTree() {};
    ~RBTree() {
        if (root != nullptr) {
            root->free();
        }
    };
    bool has_key(const K& key) override;
    void insert(const K& key, const optional<V>& value) override;
    optional<V> search(const K& key) override;
    void remove(const K& key) override;
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2) override;
    bool is_valid() override;
    void print_tree() override;

private:
    Node<K, V>* root = nullptr;
    Node<K, V>* fix_insertion(Node<K, V>* new_node);
};