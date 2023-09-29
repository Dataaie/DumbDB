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

    optional<V> search(const K& key) {
        if (key < this->key) {
            if (left == nullptr) {
                return nullopt;
            }
            return left->search(key);
        } else if (key > this->key) {
            if (right == nullptr) {
                return nullopt;
            }
            return right->search(key);
        } else {
            return value;
        }
    }

    void insert(const K& key, const optional<V>& value) {
        if (key < this->key) {
            if (left == nullptr) {
                left = new Node<K, V>(key, value, RED);
                left->parent = this;
            } else {
                left->insert(key, value);
            }
        } else if (key > this->key) {
            if (right == nullptr) {
                right = new Node<K, V>(key, value, RED);
                right->parent = this;
            } else {
                right->insert(key, value);
            }
        } else {
            this->value = value;
        }
    }
    
    void scan(const K& key1, const K& key2, vector<pair<K, optional<V>>>& results) {
        if (key1 < key) {
            if (left != nullptr) {
                left->scan(key1, key2, results);
            }
        }
        if (key1 <= key && key <= key2) {
            results.push_back(make_pair(key, value));
        }
        if (key < key2) {
            if (right != nullptr) {
                right->scan(key1, key2, results);
            }
        }
    }
};
