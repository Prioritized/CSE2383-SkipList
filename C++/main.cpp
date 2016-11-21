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

#include "SkipList.cpp"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    const int min_key = 0;
    const int max_key = 9999;
    SkipList<int> *skiplist = new SkipList<int>(min_key, max_key);

    // test code here
    ofstream outFile("output.txt");

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(min_key, max_key);

    int dist[100];
    for (int i = 0; i < 100; ++i)
        dist[i] = distr(generator);

    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
        skiplist->insert(dist[i]);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    skiplist->print_list(outFile);

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();
    
    outFile << "duration: " << duration;

    return 0;
}

