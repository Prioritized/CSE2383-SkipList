/* 
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a test file for SkipList, LinkedList, and BinarySearchTree data structures.
*
*/

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include "SkipList.h"
#include "BinarySearchTree.h"
#include "LinkedList.h"

using namespace std;


int main() {
    const long int min_key = 0;
    const long int max_key = LONG_MAX;

    // prompt for n
    long size_n;
    cout << "Enter size of input: ";
    cin >> size_n;

    // create random number generator and generate values
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<long> distr(min_key + 1, max_key - 1);

    long *dist = new long[size_n];
    for (long i = 0; i < size_n; ++i)
        dist[i] = distr(generator);
    

    // Skip List
    cout << "---Skip List----" << endl;
    SkipList<long> *skiplist = new SkipList<long>(min_key, max_key);

    // insert
    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->insert(dist[i]);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "insert: " << duration << endl;

    // search
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->search(dist[i]);
    t1 = chrono::steady_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "search: " << duration << endl << endl;


    // Binary Tree
    cout << "----Binary Tree---" << endl;

    BSTree *binarytree = new BSTree();

    // insert
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->insert(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "insert: " << duration << endl;

    // search
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->search(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "search: " << duration << endl << endl;


    // Linked List
    cout << "---Linked List----" << endl;

    LinkedList<long> *linkedlist = new LinkedList<long>();

    // insert
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        linkedlist->insert(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "insert: " << duration << endl;

    // search
    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        linkedlist->search(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << "search: " << duration << endl << endl;


    // print example skip list
    {
        ofstream SLoutFile("SL.txt");
        SkipList<int> *SLprint = new SkipList<int>(0, 10000);

        random_device print_rand_dev;
        mt19937 print_generator(rand_dev());
        uniform_int_distribution<int> print_distr(1, 9999);

        int *example_points = new int[100];
        for (int i = 0; i < 100; ++i)
            example_points[i] = print_distr(generator);

        for (int i = 0; i < 100; i++)
            SLprint->insert(example_points[i]);
        
        SLprint->print_list(SLoutFile);

        SLoutFile.close();
    }

    system("pause");
    return 0;
}

