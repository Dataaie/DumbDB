#include "memtable.hpp"
#include "config.hpp"
// #include "../../storage/include/storage.hpp"
#include <iostream>
#include <fstream>
#include <utility> 
#include <vector>

template class Memtable<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
Memtable<K, V>::Memtable() {
    tree = create_balanced_tree<K, V>(DEFAULT_BALANCED_TREE_TYPE);
    minKey = "";
    maxKey = "";
}

template <typename K, typename V>
Memtable<K, V>::~Memtable() {

}

template <typename K, typename V>
void Memtable<K, V>::put(const K& key, const optional<V>& value) {
    if(minKey == "" && maxKey == ""){
        minKey = key;
        maxKey = key;
    }else if(key < minKey){
        minKey = key;
    }else if(key > maxKey){
        maxKey = key;
    }
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
void Memtable<K, V>::flush_to_storage(string& database_path, int sst_num) {
    vector<pair<K, optional<V>>> memtable_traversal = tree->scan(minKey, maxKey);
    string sst_file = database_path + "/" + to_string(sst_num) + ".txt";
    // cout << sst_file << endl;
    ofstream outFile(sst_file);
    
    if(!outFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }
    for (pair<K, optional<V>> pair : memtable_traversal) {
        // cout << pair.first << endl;
        if (pair.second.has_value()) {
            // cout << pair.second.value() << endl;
            outFile << pair.first << ' ' << pair.second.value() << '\n';
        } 
    }
    outFile.close();
    cout << "SST flushed to storage successfully." << endl;
}