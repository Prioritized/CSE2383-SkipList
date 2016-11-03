/*
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a Skip List implementation using SkipListNode.
*
* This class is a friend class of SkipNode and therefore can access the private
* data members of SkipNode directly.
*
*/
#ifndef SKIP_LIST
#define SKIP_LIST

#include <iostream>
#include <sstream>
#include "SkipNode.h"

using namespace std;

class SkipList {
    public:
        SkipList(int min_key, int max_key);
        ~SkipList();

        void insert(int key, string data);
        string remove(int key);              //return data
        SkipNode* search(int key);        //return node
        
        void print_list();

        int heightGen();
        
        SkipNode* head;
        SkipNode* tail;
        float prob = 0.5;
        const int max_height = 8;
        int max_curr_height;
};

#endif
