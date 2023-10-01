#pragma once
#include "balanced_tree.hpp"
#include "red_black_tree.hpp"
#include <string>
#include <memory>

template <typename K, typename V>
shared_ptr<BalancedTree<K, V>> create_balanced_tree(const TreeType& type) {
    if (type == TreeType::RedBlackTree) {
        return make_shared<RBTree<K, V>>();
    } else {
        return nullptr;
    }
}