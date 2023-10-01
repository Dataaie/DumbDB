#include "memtable.hpp"
#include "config.hpp"
#include <mutex>

#define UNIQUE_LOCK unique_lock<shared_mutex> lock(rwLock);
#define SHARED_LOCK shared_lock<shared_mutex> lock(rwLock);

template class Memtable<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
Memtable<K, V>::Memtable() {
    UNIQUE_LOCK
    tree = create_balanced_tree<K, V>(DEFAULT_BALANCED_TREE_TYPE);
}

template <typename K, typename V>
Memtable<K, V>::~Memtable() {
    UNIQUE_LOCK
}

template <typename K, typename V>
void Memtable<K, V>::put(const K& key, const optional<V>& value) {
    UNIQUE_LOCK
    tree->insert(key, value);
}

template <typename K, typename V>
optional<V> Memtable<K, V>::get(const K& key) {
    SHARED_LOCK
    return tree->search(key);
}

template <typename K, typename V>
void Memtable<K, V>::remove(const K& key) {
    tree->remove(key);
}

template <typename K, typename V>
vector<pair<K, optional<V>>> Memtable<K, V>::scan(const K& key1, const K& key2) {
    SHARED_LOCK
    return tree->scan(key1, key2);
}

template <typename K, typename V>
bool Memtable<K, V>::has_key(const K& key) {
    SHARED_LOCK
    return tree->has_key(key);
}

template <typename K, typename V>
void Memtable<K, V>::flush_to_storage() {
    UNIQUE_LOCK
}