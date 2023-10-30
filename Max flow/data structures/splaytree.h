/**
 * @file splaytree.h
 * @author Noël De Faveri
 * @brief Implements a splay tree used by the Link/cut tree data structure.
 * @date 2023-10-22
 *

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stack>
#include <iostream>

namespace data_structures {

    template <typename T>
    class SplayTree {

        struct SplayNode {
            T m_value{};
            SplayNode* m_left{nullptr};
            SplayNode* m_right{nullptr};
            SplayNode* m_parent{nullptr};
        };

        public:
            SplayTree();
            SplayTree(T value);

            SplayTree& insert(T value);
            SplayTree& remove(T to_remove);
            void printInOrder() {
                printInOrder(m_root);
                std::cout << "\n";
            }

        public:
            SplayNode* m_root{nullptr};

            void splay(SplayNode* node);
            void add_child(SplayNode* p, SplayNode* c, bool left);
            void rotate_right(SplayNode* node);
            void rotate_left(SplayNode* node);
            void printInOrder(SplayNode* root) {
                if(root) {
                    std::cout << root->m_value << " ";
                    printInOrder(root->m_left);
                    printInOrder(root->m_right);
                }
            }
    };

}

#include "splaytree.tpp"

#endif
*/