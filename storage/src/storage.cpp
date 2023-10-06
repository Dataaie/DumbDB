#include "storage.hpp"
#include "config.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

template class Storage<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
Storage<K, V>::Storage(){

}

template <typename K, typename V>
Storage<K, V>::Storage(string database_path) {
    this->database_path = database_path;
    string meta_file = this->database_path + "/metafile.txt";
    if(filesystem::exists(meta_file)){
        ifstream inFile(meta_file);
        if (!inFile.is_open()) {
            cerr << "Failed to open the file." << endl;
        }

        int num;
        while (inFile >> num) {
            sst_list.push_back(num);
        }

        inFile.close();

        cout << "read from metafile: ";
        for ( int elem : sst_list) {
            cout << elem << " ";
        }
        cout << endl;
        sst_num = sst_list[0];
    }else{
        sst_list.insert(sst_list.begin(), 0);
        sst_num = 0;
    }
}

template <typename K, typename V>
Storage<K, V>::~Storage() {
    
}

template <typename K, typename V>
void Storage<K, V>::put() {
    string meta_file = this->database_path + "/metafile.txt";
    ofstream outFile(meta_file);
    if (!outFile.is_open()) {
        cerr << "Failed to open the file." << endl;
    }

    for (int elem : sst_list) {
        outFile << elem << " ";
    }

    outFile.close();
    cout << "write to metafile successfully." << endl;
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
void Storage<K, V>::update(){
    sst_list.insert(sst_list.begin() + 1, sst_num);
    sst_num++;
    sst_list[0] = sst_num;
}

template <typename K, typename V>
int Storage<K, V>::get_sst_num(){
    return sst_num;
}