#include "balanced_tree.hpp"
#include "node.hpp"

template <typename K, typename V>
class RBTree : public BalancedTree<K, V> {
public:
    RBTree() {};
    ~RBTree();
    void insert(const K& key, const optional<V>& value);
    optional<V> search(const K& key);
    void remove(const K& key);
    vector<pair<K, optional<V>>> scan(const K& key1, const K& key2);

private:
    Node<K, V>* root = nullptr;
};

template <typename K, typename V>
void RBTree<K, V>::insert(const K& key, const optional<V>& value) {
    if (root == nullptr) {
        root = new Node<K, V>(key, value, BLACK);
        return;
    }
    root->insert(key, value);
}

template <typename K, typename V>
optional<V> RBTree<K, V>::search(const K& key) {
    if (root == nullptr) {
        return nullopt;
    }
    return root->search(key);
}

template <typename K, typename V>
void RBTree<K, V>::remove(const K& key) {
    insert(key, nullopt);
}

template <typename K, typename V>
vector<pair<K, optional<V>>> RBTree<K, V>::scan(const K& key1, const K& key2) {
    vector<pair<K, optional<V>>> results;
    if (root == nullptr) {
        return results;
    }
    root->scan(key1, key2, results);
    return results;
}