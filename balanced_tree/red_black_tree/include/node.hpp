#pragma once
#include <string>
#include <optional>
#include <vector>
#include <utility>

using namespace std;

enum Color {
    RED,
    BLACK,
};

enum Direction {
    LEFT,
    RIGHT
};

template <typename K, typename V>
struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Direction parent_direction;
    Color color;
    K key;
    optional<V> value;

    Node(const K& key, const optional<V>& value, const Color& color) : key(key), value(value), color(color) {};
    bool has_key(const K& key);
    optional<V> search(const K& key);
    Node* insert(const K& key, const optional<V>& value);
    void scan(const K& key1, const K& key2, vector<pair<K, optional<V>>>& results);
    void free();
    int is_valid();
    void print(int depth=0);
};

