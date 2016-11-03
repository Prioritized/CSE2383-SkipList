/*
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a Skip List implementation using SkipNode.
*
*/
#include "SkipList.h"
#include <time.h>


SkipList::SkipList(int min_key = 0, int max_key = 1000) {
    max_curr_height = 1;
    prob = 0.5;
    srand((unsigned int)time(0));

    head = new SkipNode(min_key, max_height);
    tail = new SkipNode(max_key, max_height);
    for (int i = 0; i < max_height; i++)
        head->fwdNodes[i] = tail;
}

SkipList::~SkipList() {
    SkipNode* temp = head;
    SkipNode* next;
    while (temp) {
        next = temp->fwdNodes[1];
        delete temp;
        temp = next;
    }
}

int SkipList::heightGen(){
    int height = 1;
    while((rand()/(double) RAND_MAX) < prob && height < max_height) {
        height++;
    }
    return height;
}

void SkipList::insert(int key, string data) {
    SkipNode *update[8];
    SkipNode *curr_node = head;
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
    SkipNode *new_node = new SkipNode(key, data, height);
    for (int i = 0; i < height; i++) {
        new_node->fwdNodes[i] = update[i]->fwdNodes[i];
        update[i]->fwdNodes[i] = new_node;
    }
}

string SkipList::remove(int key) {
    SkipNode *update[8];
    SkipNode* curr_node = head;
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
        string data = curr_node->data;
        delete curr_node;
        curr_node = nullptr;
        // update max_curr_height
        while (max_curr_height > 0 && head->fwdNodes[max_curr_height] == NULL) {
            max_curr_height--;
        }
        return data;
    }
    else {
        return "fail";
    }
}

SkipNode* SkipList::search(int key) {
    SkipNode* curr_node = head;
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
        return NULL;
    }
}


void SkipList::print_list() {
    stringstream sstr;
    for (int i = max_curr_height - 1; i >= 0; i--) {
        SkipNode* curr_node = head->fwdNodes[i];
        sstr << "HEAD -- ";
        while (curr_node != tail) {
            sstr << "(" << curr_node->key << ", " << curr_node->data << ") -- ";
            curr_node = curr_node->fwdNodes[i];
        }
        sstr << "TAIL";
        sstr << endl;
    }
    cout << sstr.str() << endl;
}
