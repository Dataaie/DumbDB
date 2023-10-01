#include "node.hpp"

template <typename K, typename V>
inline void add_child(Node<K, V>* parent, Node<K, V>* child, const Direction& direction) {
    if (parent != nullptr) {
        if (direction == Direction::LEFT) {
        parent->left = child;
        } else {
            parent->right = child;
        }
    }
    if (child != nullptr) {
        child->parent = parent;
        child->parent_direction = direction;
    }
}

template <typename K, typename V>
inline bool is_brother_Red(Node<K, V>* node) {
    Node<K, V>* brother;
    if (node->parent_direction == Direction::LEFT) {
        brother = node->parent->right;
    } else {
        brother = node->parent->left;
    }
    if (brother == nullptr || brother->color == BLACK) {
        return false;
    }
    return true;
}

template <typename K, typename V>
inline void set_brother_color(Node<K, V>* node, const Color& color) {
    if (node->parent_direction == Direction::LEFT) {
        node->parent->right->color = color;
    } else {
        node->parent->left->color = color;
    }
}

template <typename K, typename V>
inline void set_parent_color(Node<K, V>* node, const Color& color) {
    node->parent->color = color;
}