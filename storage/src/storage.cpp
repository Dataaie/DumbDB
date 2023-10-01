#include "storage.hpp"
#include "config.hpp"

template class Storage<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
Storage<K, V>::Storage() {
    
}

template <typename K, typename V>
Storage<K, V>::~Storage() {
    
}

template <typename K, typename V>
void Storage<K, V>::put(const K& key, const optional<V>& value) {
    
}

template <typename K, typename V>
optional<V> Storage<K, V>::get(const K& key) {
    return nullopt;    
}

template <typename K, typename V>
void Storage<K, V>::remove(const K& key) {

}

template <typename K, typename V>
vector<pair<K, optional<V>>> Storage<K, V>::scan(const K& key1, const K& key2) {
    return vector<pair<K, optional<V>>>();
}

template <typename K, typename V>
void Storage<K, V>::open(const string& database_name) {
    database_name_ = database_name;
}

