#pragma once
#include <string>
#include <optional>
#include <vector>
#include <utility>

using namespace std;

enum Color {
    RED,
    BLACK
};

enum Direction {
    LEFT,
    RIGHT
};

enum Rotation {
    LEFT_ROTATION,
    RIGHT_ROTATION
};

template <typename K, typename V>
struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Color color;
    K key;
    optional<V> value;

    Node(const K& key, const optional<V>& value, const Color& color) : key(key), value(value), color(color) {};
    optional<V> search(const K& key);
    void insert(const K& key, const optional<V>& value);
    void scan(const K& key1, const K& key2, vector<pair<K, optional<V>>>& results);
    void free();
};

