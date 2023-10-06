#include "config.hpp"
#include <iostream>
#include "dumb.hpp"
#include "memtable.hpp"
#include "storage.hpp"
#include "balanced_tree_factory.hpp"
#include <filesystem>

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
    bool is_open_ = false;
    string cur_database;
    Memtable<K, V> memtable;
    Storage<K, V> storage;
};

template <typename K, typename V>
void DumbDB<K, V>::Open(const string& database_name) {
    if (is_open_) {
        cout << "Database " << database_name << " already open.\n";
        return;
    }
    cur_database = "./data/" + database_name;
    if(!filesystem::exists(cur_database)){
        filesystem::create_directory(cur_database);
        cout << "Database " << database_name << " created.\n" << endl;
    }
    memtable = Memtable<K, V>();
    storage = Storage<K, V>(cur_database);
    is_open_ = true;
    cout << "Database " << database_name << " opened.\n" << endl;
}

template <typename K, typename V>
void DumbDB<K, V>::Put(const K& key, const optional<V>& value) {
    memtable.put(key, value);
}

template <typename K, typename V>
optional<V> DumbDB<K, V>::Get(const K& key) {
    auto result = memtable.get(key);
    if (result.has_value()) {
        return result;
    }
    if (memtable.has_key(key)) {
        return result;
    }
    return storage.get(key);
}

template <typename K, typename V>
void DumbDB<K, V>::Delete(const K& key) {
    memtable.remove(key);
}

template <typename K, typename V>
vector<pair<K, optional<V>>> DumbDB<K, V>::Scan(const K& key1, const K& key2) {
    auto all_data = create_balanced_tree<K, V>(DEFAULT_BALANCED_TREE_TYPE);
    for (auto& pair : storage.scan(key1, key2)) {
        all_data->insert(pair.first, pair.second);
    }
    for (auto& pair : memtable.scan(key1, key2)) {
        all_data->insert(pair.first, pair.second);
    }
    return all_data->scan(key1, key2);
}

template <typename K, typename V>
void DumbDB<K, V>::Close() {
    if (!is_open_) {
        cout << "Database already closed.\n";
        return;
    }
    int sst_num = storage.get_sst_num();
    memtable.flush_to_storage(cur_database, sst_num);
    storage.update();
    storage.put();
    is_open_ = false;
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