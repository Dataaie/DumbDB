#include <iostream>
#include "dumb.h"

template class DumbDB<std::string, std::string>;

template <typename K, typename V>
void DumbDB<K, V>::Open(const std::string& database_name) {
    std::cout << "Database " << database_name << " opened.\n";
}

template <typename K, typename V>
void DumbDB<K, V>::Put(const K& key, const V& value) {
    db_[key] = value;
}

template <typename K, typename V>
V DumbDB<K, V>::Get(const K& key) {
    auto it = db_.find(key);
    if (it != db_.end()) {
        return it->second;
    }
    return V(); // Return default-constructed value
}

template <typename K, typename V>
std::vector<std::pair<K, V>> DumbDB<K, V>::Scan(const K& key1, const K& key2) {
    std::vector<std::pair<K, V>> results;
    for (const auto& kv : db_) {
        if (kv.first >= key1 && kv.first <= key2) {
            results.push_back(kv);
        }
    }
    return results;
}

template <typename K, typename V>
void DumbDB<K, V>::Close() {
    std::cout << "Database closed.\n";
}
