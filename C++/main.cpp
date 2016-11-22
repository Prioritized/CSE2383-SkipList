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
    const unsigned int min_key = 0;
    const unsigned int max_key = 9999;
    ofstream timeOut("Time.txt");

    // prompt for n
    //unsigned int size_n;
    //cout << "Enter size of input: ";
    //cin >> size_n;

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(min_key + 1, max_key - 1);

    int dist[100];
    for (int i = 0; i < 100; ++i)
        dist[i] = distr(generator);

    // Skip List
    ofstream SLoutFile("SL.txt");

    SkipList<int> *skiplist = new SkipList<int>(min_key, max_key);

    chrono::steady_clock::time_point t0 = chrono::steady_clock::now();
    for (int i = 0; i < 100; i++)
        skiplist->insert(dist[i]);
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    skiplist->print_list(SLoutFile);

    auto duration = chrono::duration_cast<chrono::microseconds>(t1 - t0).count();

    SLoutFile.close();

    timeOut << "SL duration:  " << duration;

    timeOut.close();

    return 0;
}

