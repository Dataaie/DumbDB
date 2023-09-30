#include "config.hpp"
#include "red_black_tree.hpp"

template class RBTree<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
void RBTree<K, V>::insert(const K& key, const optional<V>& value) {
    if (root == nullptr) {
        root = new Node<K, V>(key, value, BLACK);
        return;
    }
    root->insert(key, value);
};

template <typename K, typename V>
optional<V> RBTree<K, V>::search(const K& key) {
    if (root == nullptr) {
        return nullopt;
    }
    return root->search(key);
};

template <typename K, typename V>
void RBTree<K, V>::remove(const K& key) {
    insert(key, nullopt);
};

template <typename K, typename V>
vector<pair<K, optional<V>>> RBTree<K, V>::scan(const K& key1, const K& key2) {
    vector<pair<K, optional<V>>> results;
    if (root == nullptr) {
        return results;
    }
    root->scan(key1, key2, results);
    return results;
};

template <typename K, typename V>
void RBTree<K, V>::free() {
    if (root != nullptr) {
        root->free();
    }
};