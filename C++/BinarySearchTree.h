/*
* BinarySearchTree.h
*
* original author:  Alex Allain
*   from www.cprogramming.com/tutorial/lesson18.html
*
* secondary author: Jack Fletcher
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is the header file for an implementation of a binary search tree.
* Everything is the same as Alex's original implementation except for
* the class names and data types.
* 
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H


struct BSTNode {
    long key_value;
    BSTNode *left;
    BSTNode *right;
};


class BSTree {
    public:
        BSTree();
        ~BSTree();

        void remove(long key);
        void insert(long key);
        BSTNode *search(long key);
        void destroy_tree();

    private:
        void destroy_tree(BSTNode *leaf);
        void insert(long key, BSTNode *leaf);
        BSTNode *search(long key, BSTNode *leaf);

        BSTNode *root;
};

#endif
