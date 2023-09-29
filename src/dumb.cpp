#include <iostream>
#include "dumb.hpp"

template class IDumbDB<KEY_TYPE, optional<VALUE_TYPE>>;
template IDumbDB<KEY_TYPE, VALUE_TYPE>* CreateDumbDB<KEY_TYPE, VALUE_TYPE>();

template <typename K, typename V>
class DumbDB : public IDumbDB<K, V> {
public:
    virtual ~DumbDB();
    virtual void Open(const string& database_name);
    virtual void Put(const K& key, const optional<V>& value);
    virtual optional<V> Get(const K& key);
    virtual void Delete(const K& key);
    virtual vector<pair<K, optional<V>>> Scan(const K& key1, const K& key2);
    virtual void Close();
private:
    bool is_open_ = false;
    unordered_map<K, optional<V>> db_;
};

template <typename K, typename V>
void DumbDB<K, V>::Open(const string& database_name) {
    if (is_open_) {
        cout << "Database " << database_name << " already open.\n";
        return;
    }
    cout << "Database " << database_name << " opened.\n";
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
vector<pair<K, optional<V>>> DumbDB<K, V>::Scan(const K& key1, const K& key2) {
    vector<pair<K, optional<V>>> results;
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
        cout << "Database already closed.\n";
        return;
    }
    cout << "Database closed.\n";
}

template <typename K, typename V>
DumbDB<K, V>::~DumbDB() {
    this->Close();
}

template <typename K, typename V>
IDumbDB<K, V>* CreateDumbDB() {
    return new DumbDB<K, V>();
}