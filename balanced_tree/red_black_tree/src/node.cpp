#include "node.hpp"
#include "config.hpp"
#include "utils.hpp"

template class Node<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
bool Node<K, V>::has_key(const K& key) {
    if (key < this->key) {
        if (left == nullptr) {
            return false;
        }
        return left->has_key(key);
    } else if (key > this->key) {
        if (right == nullptr) {
            return false;
        }
        return right->has_key(key);
    } else {
        return true;
    }
};

template <typename K, typename V>
optional<V> Node<K, V>::search(const K& key) {
    if (key < this->key) {
        if (left == nullptr) {
            return nullopt;
        }
        return left->search(key);
    } else if (key > this->key) {
        if (right == nullptr) {
            return nullopt;
        }
        return right->search(key);
    } else {
        return value;
    }
};

template <typename K, typename V>
Node<K, V>* Node<K, V>::insert(const K& key, const optional<V>& value) {
    if (key < this->key) {
        Node<K, V>* new_node;
        if (left == nullptr) {
            add_child(this, new Node<K, V>(key, value, RED), Direction::LEFT);
            return this->left;
        } else {
            return left->insert(key, value);
        }
    } else if (key > this->key) {
        Node<K, V>* new_node;
        if (right == nullptr) {
            add_child(this, new Node<K, V>(key, value, RED), Direction::RIGHT);
            return this->right;
        } else {
            return right->insert(key, value);
        }
    } else {
        this->value = value;
        return nullptr;
    }
};

template <typename K, typename V>
void Node<K, V>::scan(const K& key1, const K& key2, vector<pair<K, optional<V>>>& results) {
    if (key1 < key) {
        if (left != nullptr) {
            left->scan(key1, key2, results);
        }
    }
    if (key1 <= key && key <= key2) {
        results.push_back(make_pair(key, value));
    }
    if (key < key2) {
        if (right != nullptr) {
            right->scan(key1, key2, results);
        }
    }
};

template <typename K, typename V>
void Node<K, V>::free() {
    if (left != nullptr) {
        left->free();
    }
    if (right != nullptr) {
        right->free();
    }
    delete this;
};