#include "config.hpp"
#include <iostream>
#include "dumb.hpp"
#include "memtable.hpp"
#include "storage.hpp"
#include "balanced_tree_factory.hpp"
#include <mutex>

#define UNIQUE_LOCK unique_lock<shared_mutex> lock(rwLock);
#define SHARED_LOCK shared_lock<shared_mutex> lock(rwLock);

template class IDumbDB<KEY_TYPE, VALUE_TYPE>;
template IDumbDB<KEY_TYPE, VALUE_TYPE>* CreateDumbDB<KEY_TYPE, VALUE_TYPE>();

template <typename K, typename V>
class DumbDB : public IDumbDB<K, V> {
public:
    ~DumbDB();
    void Open(const string& database_name) override;
    void Put(const K& key, const optional<V>& value) override;
    optional<V> Get(const K& key) override;
    void Delete(const K& key) override;
    vector<pair<K, optional<V>>> Scan(const K& key1, const K& key2) override;
    void Close() override;
private:
    string database_name_;
    bool is_open_ = false;
    Memtable<K, V> memtable_;
    Storage<K, V> storage_;
    shared_mutex rwLock;
};

template <typename K, typename V>
void DumbDB<K, V>::Open(const string& database_name) {
    UNIQUE_LOCK
    if (is_open_) {
        cout << "Database " << database_name << " already open.\n";
        return;
    }
    is_open_ = true;
    database_name_ = database_name;
    storage_.open(database_name);
    cout << "Database " << database_name << " opened.\n";
}

template <typename K, typename V>
void DumbDB<K, V>::Put(const K& key, const optional<V>& value) {
    UNIQUE_LOCK
    memtable_.put(key, value);
}

template <typename K, typename V>
optional<V> DumbDB<K, V>::Get(const K& key) {
    SHARED_LOCK
    auto result = memtable_.get(key);
    if (result.has_value()) {
        return result;
    }
    if (memtable_.has_key(key)) {
        return result;
    }
    return storage_.get(key);
}

template <typename K, typename V>
void DumbDB<K, V>::Delete(const K& key) {
    UNIQUE_LOCK
    memtable_.remove(key);
}

template <typename K, typename V>
vector<pair<K, optional<V>>> DumbDB<K, V>::Scan(const K& key1, const K& key2) {
    SHARED_LOCK
    auto all_data = create_balanced_tree<K, V>(DEFAULT_BALANCED_TREE_TYPE);
    for (auto& pair : storage_.scan(key1, key2)) {
        all_data->insert(pair.first, pair.second);
    }
    for (auto& pair : memtable_.scan(key1, key2)) {
        all_data->insert(pair.first, pair.second);
    }
    return all_data->scan(key1, key2);
}

template <typename K, typename V>
void DumbDB<K, V>::Close() {
    UNIQUE_LOCK
    if (!is_open_) {
        cout << "Database already closed.\n";
        return;
    }
    memtable_.flush_to_storage();
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