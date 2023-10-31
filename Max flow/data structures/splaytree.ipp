/**
#ifndef SPLAY_TREE_IPP
#define SPLAY_TREE_IPP

#include <iostream>

namespace data_structures {

    template<typename T>
    SplayTree<T>::SplayTree() {}

    template<typename T>
    SplayTree<T>::SplayTree(T value) {
        m_root = new SplayNode{value};
    }

    template<typename T>
    SplayTree<T>& SplayTree<T>::insert(T value) {
        SplayNode* to_add = new SplayNode{value};
        if(!m_root) {
            m_root = to_add;
        } else {
            SplayNode* current = m_root;
            while(true) {
                if(current->m_value == value) {
                    to_add = current;
                    break;
                }
                if(current->m_value < value) {
                    if(!current->m_right) {
                        add_child(current, to_add, false);
                        break;
                    }
                    current = current->m_right;
                } else {
                    if(!current->m_left) {
                        add_child(current, to_add, true);
                        break;
                    }
                    current = current->m_left;
                }
            }
        }
        splay(to_add);
        return *this;
    }

    template<typename T>
    SplayTree<T>& SplayTree<T>::remove(T to_remove) {
        std::cout << "DELETE\n";
        return *this;
    }

    template<typename T>
    void SplayTree<T>::splay(SplayNode* node) {
        if(!node) { return; }
        while(node->m_parent) {
            if(!node->m_parent->m_parent) {
                if(node->m_parent->m_left == node) {
                    rotate_right(node->m_parent);
                } else {
                    rotate_left(node->m_parent);
                }
            } else if(node->m_parent->m_left == node && node->m_parent->m_parent->m_left == node->m_parent) {
                rotate_right(node->m_parent->m_parent);
                rotate_right(node->m_parent);
            } else if(node->m_parent->m_right == node && node->m_parent->m_parent->m_right == node->m_parent) {
                rotate_left(node->m_parent->m_parent);
                rotate_left(node->m_parent);
            } else if(node->m_parent->m_left == node && node->m_parent->m_parent->m_right == node->m_parent) {
                rotate_right(node->m_parent);
                rotate_left(node->m_parent);
            } else {
                rotate_left(node->m_parent);
                rotate_right(node->m_parent);
            }
        }
    }

    template<typename T>
    void SplayTree<T>::add_child(SplayNode* p, SplayNode* c, bool left) {
        if(left) {
            p->m_left = c;
        } else {
            p->m_right = c;
        }
        c->m_parent = p;
        splay(c);
    }

    template<typename T>
    void SplayTree<T>::rotate_left(SplayNode* node) {
        SplayNode* node_right = node->m_right;
        if(node_right) {
            SplayNode* node_left = node_right->m_left;
            node->m_right = node_left;
            if(node_left) {
                node_left->m_parent = node;
            }
            node_right->m_parent = node->m_parent;
        }
        if(!node->m_parent) {
            m_root = node;
            std::cout << m_root->m_value;
        } else if(node == node->m_parent->m_left) {
            node->m_parent->m_left = node_right;
        } else {
            node->m_parent->m_right = node_right;
        }
        if(node_right) {
            node_right->m_left = node;
        }
        node->m_parent = node_right;
    }
        
    template<typename T>
    void SplayTree<T>::rotate_right(SplayNode* node) {
        SplayNode* node_left = node->m_left;
        if(node_left) {
            SplayNode* node_right = node_left->m_right;
            node->m_left = node_right;
            if(node_right) {
                node_right->m_parent = node;
            }
            node_left->m_parent = node->m_parent;
        }
        if(!node->m_parent) {
            m_root = node;
            std::cout << m_root->m_value;
        } else if(node == node->m_parent->m_left) {
            node->m_parent->m_left = node_left;
        } else {
            node->m_parent->m_right = node_left;
        }
        if(node_left) {
            node_left->m_right = node;
        }
        node->m_parent = node_left;
    }
}

#endif
*/