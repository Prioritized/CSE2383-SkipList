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

#include "SkipList.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    int min_key = 0;
    int max_key = 100;
    SkipList *skiplist = new SkipList(min_key, max_key);

    // write your test code here

    // read in file
    ifstream inFile("input1.txt");

    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    string line;
    int key;
    string state;
    int i = 0;
    while (inFile >> key >> state) {
        skiplist->insert(key, state);
        cout << i++ << endl;
    }

    skiplist->print_list();

    inFile.close();


    return 0;
}

