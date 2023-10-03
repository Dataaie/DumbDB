#include "memtable.hpp"
#include "config.hpp"

template class Memtable<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
Memtable<K, V>::Memtable() {
    tree = create_balanced_tree<K, V>(DEFAULT_BALANCED_TREE_TYPE);
}

template <typename K, typename V>
Memtable<K, V>::~Memtable() {
    
}

template <typename K, typename V>
void Memtable<K, V>::put(const K& key, const optional<V>& value) {
    tree->insert(key, value);
}

template <typename K, typename V>
optional<V> Memtable<K, V>::get(const K& key) {
    return tree->search(key);
}

template <typename K, typename V>
void Memtable<K, V>::remove(const K& key) {
    tree->remove(key);
}

template <typename K, typename V>
vector<pair<K, optional<V>>> Memtable<K, V>::scan(const K& key1, const K& key2) {
    return tree->scan(key1, key2);
}

template <typename K, typename V>
bool Memtable<K, V>::has_key(const K& key) {
    return tree->has_key(key);
}

template <typename K, typename V>
void Memtable<K, V>::flush_to_storage() {

}