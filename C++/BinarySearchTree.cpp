/*
* BinarySearchTree.cpp
*
* original author:  Alex Allain
*   from www.cprogramming.com/tutorial/lesson18.html
*
* secondary author: Jack Fletcher
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is an implementation of a binary search tree.
* Everything is the same as Alex's original implementation except for
* the class names and data types.
*
*/

#include <iostream>
#include "BinarySearchTree.h"


BSTree::BSTree() {
    root = NULL;
}

BSTree::~BSTree() {
    destroy_tree();
}

void BSTree::destroy_tree(BSTNode *leaf) {
    if (leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void BSTree::insert(long key, BSTNode *leaf) {
    if (key < leaf->key_value) {
        if (leaf->left != NULL)
            insert(key, leaf->left);
        else {
            leaf->left = new BSTNode;
            leaf->left->key_value = key;
            leaf->left->left = NULL;    //Sets the left child of the child node to null
            leaf->left->right = NULL;   //Sets the right child of the child node to null
        }
    }
    else if (key >= leaf->key_value) {
        if (leaf->right != NULL)
            insert(key, leaf->right);
        else {
            leaf->right = new BSTNode;
            leaf->right->key_value = key;
            leaf->right->left = NULL;  //Sets the left child of the child node to null
            leaf->right->right = NULL; //Sets the right child of the child node to null
        }
    }
}

BSTNode* BSTree::search(long key, BSTNode *leaf) {
    if (leaf != NULL) {
        if (key == leaf->key_value)
            return leaf;
        if (key < leaf->key_value)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else return NULL;
}

void BSTree::insert(long key) {
    if (root != NULL)
        insert(key, root);
    else {
        root = new BSTNode;
        root->key_value = key;
        root->left = NULL;
        root->right = NULL;
    }
}

BSTNode* BSTree::search(long key) {
    return search(key, root);
}

void BSTree::remove(long key) {
    BSTNode *dnode = root;
    BSTNode *parent = NULL;
    while (dnode != NULL) {
        if (key == dnode->key_value) {
            if (dnode->left == NULL && dnode->right == NULL) {      // no children
                if (parent == NULL) {
                    root = NULL;
                }
                else {
                    if (dnode == parent->left) {
                        parent->left = NULL;
                    }
                    else {
                        parent->right = NULL;
                    }
                }
            }
            else if (dnode->left != NULL && dnode->right != NULL) { // two children
                BSTNode* sub = dnode->left;
                BSTNode* subparent = dnode;
                while (sub->right != NULL) {
                    subparent = sub;
                    sub = sub->right;
                }
                if (sub->left == NULL) {
                    if (sub == subparent->left) {
                        subparent->left = NULL;
                    }
                    else {
                        subparent->right = NULL;
                    }
                }
                else {
                    BSTNode* child;
                    if (sub->left != NULL) {
                        child = sub->left;
                    }
                    else {
                        child = sub->right;
                    }
                    if (sub == subparent->left) {
                        subparent->left = child;
                    }
                    else {
                        subparent->right = child;
                    }
                }
                if (parent == NULL) {
                    root = sub;
                }
                else {
                    if (dnode == parent->left) {
                        parent->left = sub;
                    }
                    else {
                        parent->right = sub;
                    }
                }
                sub->left = dnode->left;
                sub->right = dnode->right;
            }
            else {                                                  // one child
                BSTNode* child;
                if (dnode->left != NULL) {
                    child = dnode->left;
                }
                else {
                    child = dnode->right;
                }
                if (parent == NULL) {
                    root = child;
                }
                else {
                    if (dnode == parent->left) {
                        parent->left = child;
                    }
                    else {
                        parent->right = child;
                    }
                }
            }
            delete dnode;
            return;
        }
        else if (key < dnode->key_value){
            parent = dnode;
            dnode = dnode->left;
        }
        else {
            parent = dnode;
            dnode = dnode->right;
        }
    }
    std::cout << "Key: " << key << " not found." << std::endl;
}

void BSTree::destroy_tree() {
    destroy_tree(root);
}
