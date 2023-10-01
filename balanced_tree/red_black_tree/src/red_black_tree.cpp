#include "config.hpp"
#include "red_black_tree.hpp"
#include "utils.cpp"
#include <iostream>

template class RBTree<KEY_TYPE, VALUE_TYPE>;

template <typename K, typename V>
bool RBTree<K, V>::has_key(const K& key) {
    if (root == nullptr) {
        return false;
    }
    return root->has_key(key);
};

template <typename K, typename V>
void RBTree<K, V>::insert(const K& key, const optional<V>& value) {
    if (root == nullptr) {
        root = new Node<K, V>(key, value, BLACK);
        return;
    }
    root = this->fix_insertion(root->insert(key, value));
};

template <typename K, typename V>
optional<V> RBTree<K, V>::search(const K& key) {
    if (root == nullptr) {
        return nullopt;
    }
    return root->search(key);
};

template <typename K, typename V>
void RBTree<K, V>::remove(const K& key) {
    insert(key, nullopt);
};

template <typename K, typename V>
vector<pair<K, optional<V>>> RBTree<K, V>::scan(const K& key1, const K& key2) {
    vector<pair<K, optional<V>>> results;
    if (root == nullptr) {
        return results;
    }
    root->scan(key1, key2, results);
    return results;
};

/* 
    maintain red black tree 
*/

template <typename K, typename V>
inline Node<K, V>* invert(Node<K, V>* current, Node<K, V>* child) {
    auto parent = current->parent;
    auto parent_direction = current->parent_direction;
    if (child->parent_direction == RIGHT) {
        add_child(current, child->left, RIGHT);
        add_child(child, current, LEFT);
        add_child(parent, child, parent_direction);
    } else {
        add_child(current, child->right, LEFT);
        add_child(child, current, RIGHT);
        add_child(parent, child, parent_direction);
    }
    return child;
};

template <typename K, typename V>
inline Node<K, V>* adjust_upward(Node<K, V>* current, Node<K, V>* child) {
    if (child->color == Color::RED) {
        if (current->color == BLACK) {
            /* case 1:
                    B(current)
                    /
                    R(child)
            */
            return current;
        } else {
            if (current->parent == nullptr) {
                /* case 4:
                        R(parent, root)
                        /
                        R(child)
                */
                current->color = BLACK;
                return current;
                /* become:
                        B(parent, root)
                        /
                        R(child)
                */
            }
            if (is_brother_Red(current)) {
                /* case 2:
                            B(parent)
                            /       \
                        R(current)  R(brother)
                        /       
                    R(child)
                */
                current->color = BLACK;
                set_brother_color(current, BLACK);
                set_parent_color(current, RED);
                return current;
                /* become:
                            R(parent)
                            /       \
                        B(current)  B(brother)
                        /       
                    R(child)
                */
            } else {
                if (current->parent_direction != child->parent_direction) {
                    /* case 5:
                                B(parent)
                                /       \
                            R(current)  B(brother)
                                 \       
                                R(child)
                        or 
                                B(parent)
                                /       \
                            B(brother)  R(current)
                                        /       
                                    R(child)
                    */
                    current = invert(current, child);
                    /* become case 6
                    */
                }
                /* case 6:
                              B(parent)
                              /       \
                          R(current)  B(brother)
                            /       
                        R(child)
                    or
                            B(parent)
                            /       \
                        B(brother)  R(current)
                                        \      
                                      R(child)
                */
                current->color = BLACK;
                set_parent_color(current, RED);
                return invert(current->parent, current);
                /* become:
                            B(current)
                            /       \
                        R(child)   R(parent)
                                        \
                                    R(brother)
                    or 
                            B(current)
                            /       \
                        R(parent)   R(child)
                         /
                    R(brother)
                */
            }
        }
    } else {
        return current;
    }
}

template <typename K, typename V>
Node<K, V>* RBTree<K, V>::fix_insertion(Node<K, V>* new_node) {
    int count = 0;
    while (new_node->parent != nullptr) {
        new_node = adjust_upward(new_node->parent, new_node);
    }
    // case3
    new_node->color = BLACK;
    return new_node; 
}

template <typename K, typename V>
bool RBTree<K, V>::is_valid() {
    if (root == nullptr) {
        return true;
    }
    if (root->color == RED) {
        return false;
    }
    return root->is_valid() != -1;
}

template <typename K, typename V>
void RBTree<K, V>::print_tree() {
    if (root == nullptr) {
        cout << "empty tree" << endl;
        return;
    }
    root->print();
}