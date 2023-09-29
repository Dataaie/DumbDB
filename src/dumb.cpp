#include <iostream>
#include "dumb.h"

template class IDumbDB<string, optional<string>>;
template IDumbDB<string, string>* CreateDumbDB<string, string>();

template <typename K, typename V>
class DumbDB : public IDumbDB<K, V> {
public:
    virtual ~DumbDB();
    virtual void Open(const std::string& database_name);
    virtual void Put(const K& key, const optional<V>& value);
    virtual optional<V> Get(const K& key);
    virtual void Delete(const K& key);
    virtual std::vector<std::pair<K, optional<V>>> Scan(const K& key1, const K& key2);
    virtual void Close();
private:
    std::unordered_map<K, optional<V>> db_;
    bool is_open_ = false;
};

template <typename K, typename V>
void DumbDB<K, V>::Open(const std::string& database_name) {
    if (is_open_) {
        std::cout << "Database " << database_name << " already open.\n";
        return;
    }
    std::cout << "Database " << database_name << " opened.\n";
}

template <typename K, typename V>
void DumbDB<K, V>::Put(const K& key, const optional<V>& value) {
    db_[key] = value;
}

template <typename K, typename V>
optional<V> DumbDB<K, V>::Get(const K& key) {
    auto it = db_.find(key);
    if (it != db_.end()) {
        return it->second;
    }
    return nullopt;
}

template <typename K, typename V>
void DumbDB<K, V>::Delete(const K& key) {
    db_.erase(key);
}

template <typename K, typename V>
std::vector<std::pair<K, optional<V>>> DumbDB<K, V>::Scan(const K& key1, const K& key2) {
    std::vector<std::pair<K, optional<V>>> results;
    for (const auto& kv : db_) {
        if (kv.first >= key1 && kv.first <= key2) {
            results.push_back(kv);
        }
    }
    return results;
}

template <typename K, typename V>
void DumbDB<K, V>::Close() {
    if (!is_open_) {
        std::cout << "Database already closed.\n";
        return;
    }
    std::cout << "Database closed.\n";
}

template <typename K, typename V>
DumbDB<K, V>::~DumbDB() {
    this->Close();
}

template <typename K, typename V>
IDumbDB<K, V>* CreateDumbDB()
{
    return new DumbDB<K, V>();
}