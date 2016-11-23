/*
* SkipList.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a Skip List implementation using node objects from SkipNode.h.
*
*/

#include "SkipList.h"
#include <time.h>
#include <ostream>
#include <fstream>


template <typename T>
SkipList<T>::SkipList(T min_key, T max_key) {
    max_curr_height = 1;
    prob = 0.5;
    srand((unsigned int)time(0));

    head = new SkipNode<T>(min_key, max_height);
    tail = new SkipNode<T>(max_key, max_height);
    for (int i = 0; i < max_height; i++)
        head->fwdNodes[i] = tail;
}

template <typename T>
SkipList<T>::~SkipList() {
    SkipNode<T> *temp = head;
    SkipNode<T> *next;
    while (temp) {
        next = temp->fwdNodes[1];
        delete temp;
        temp = next;
    }
}

template <typename T>
int SkipList<T>::heightGen(){
    int height = 1;
    while((rand()/(double) RAND_MAX) < prob && height < max_height) {
        height++;
    }
    return height;
}

template <typename T>
void SkipList<T>::insert(T key) {
    SkipNode<T> *update[max_height];
    SkipNode<T> *curr_node = head;
    auto lag_node = curr_node;
    for (int height = max_height - 1; height >= 0; height--) {
        while (curr_node->fwdNodes[height]->key < key) {
            lag_node = curr_node;
            curr_node = curr_node->fwdNodes[height];
        }
        update[height] = curr_node;
        curr_node = lag_node;
    }
    curr_node = curr_node->fwdNodes[0];

    int height = heightGen();
    if (height > max_curr_height) {
        for (int i = max_curr_height; i <= height - 1; i++) {
            update[i] = head;
        }
        max_curr_height = height;
    }
    SkipNode<T> *new_node = new SkipNode<T>(key, height);
    for (int i = 0; i < height; i++) {
        new_node->fwdNodes[i] = update[i]->fwdNodes[i];
        update[i]->fwdNodes[i] = new_node;
    }
}

template <typename T>
bool SkipList<T>::remove(T key) {
    SkipNode<T> *update[max_height];
    SkipNode<T> *curr_node = head;
    for (int height = max_curr_height - 1; height >= 0; height--) {
        while (curr_node->fwdNodes[height]->key < key) {
            curr_node = curr_node->fwdNodes[height];
        }
        update[height] = curr_node;
    }
    curr_node = curr_node->fwdNodes[0];
    if (curr_node->key = key) {
        for (int height = 0; height < max_curr_height; height++) {
            if (update[height]->fwdNodes[height] != curr_node) {
                break;
            }
            update[height]->fwdNodes[height] = curr_node->fwdNodes[height];
        }
        delete curr_node;
        curr_node = nullptr;
        // update max_curr_height
        while (max_curr_height > 0 && head->fwdNodes[max_curr_height] == NULL) {
            max_curr_height--;
        }
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
SkipNode<T> *SkipList<T>::search(T key) {
    SkipNode *curr_node = head;
    for (int height = max_curr_height - 1; height >= 0; height--) {
        while (curr_node->fwdNodes[height]->key < key) {
            curr_node = curr_node->fwdNodes[height];
        }
    }
    curr_node = curr_node->fwdNodes[0];
    if (curr_node->key == key) {
        return curr_node;
    }
    else {
        return nullptr;
    }
}

template <typename T>
void SkipList<T>::print_list(ofstream& outFile) {
    // start at head
    SkipNode<T> *curr_node = head;
    for (int i = 0; i < max_height; i++) {
        outFile << "[HEAD]";
    }
    outFile << endl;

    //iterate through the skiplist
    char value[5] = "0000";
    while (curr_node->fwdNodes[0] != tail) {
        stringstream sstr;
        curr_node = curr_node->fwdNodes[0];
        for (int i = 0; i < curr_node->height; i++) {
            sprintf_s(value, "%04d", curr_node->key);
            sstr << "[" << value << "]";
        }
        sstr << endl;
        outFile << sstr.str();
    }

    // found tail
    for (int i = 0; i < max_height; i++)
    {
        outFile << "[TAIL]";
    }
    outFile << endl;
}
