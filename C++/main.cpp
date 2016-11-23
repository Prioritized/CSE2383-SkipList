/* 
* main.cpp
*
* author:  Jack Fletcher
* date:    10/23/2016
*
* CSE 2383 Data Structures
* Honors Assignment
*
* This is a test file for SkipList.cpp.
*
*/

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include "SkipList.cpp"
#include "BinarySearchTree.h"

using namespace std;

int main() {
    const long int min_key = 0;
    const long int max_key = LONG_MAX;
    //ofstream timeOut("Time.txt");

    // prompt for n
    long size_n;
    cout << "Enter size of input: ";
    cin >> size_n;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<long> distr(min_key + 1, max_key - 1);

    long* dist = new long[size_n];
    for (long i = 0; i < size_n; ++i)
        dist[i] = distr(generator);

    // Skip List
    //ofstream SLoutFile("SL.txt");

    SkipList<long> *skiplist = new SkipList<long>(min_key, max_key);

    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        skiplist->insert(dist[i]);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    //skiplist->print_list(SLoutFile);

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << duration << endl;

    //SLoutFile.close();

    
    // Binary Tree
    BSTree* binarytree = new BSTree();

    t0 = chrono::steady_clock::now();
    for (long i = 0; i < size_n; i++)
        binarytree->insert(dist[i]);
    t1 = chrono::steady_clock::now();

    duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    cout << duration << endl;

    system("pause");
    return 0;
}

