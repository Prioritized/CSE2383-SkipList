/*
* SkipNode.h
*
* author: Jack Fletcher
* date: 10/23/2016
*
* This is a node class used to build a skip list.  
* 
* Implementation is based on William Pugh's pseudocode in his paper titled
* "Skip Lists: A Probabilistic Alternative to Balanced Trees"
*
*
*/

#ifndef SKIP_LIST_NODE_H
#define SKIP_LIST_NODE_H

template <typename T> class SkipList;

template <typename T>
class SkipNode {
public:
    inline SkipNode(T key, int height);
    inline SkipNode(int height);
    inline ~SkipNode();
        
    T key;
    int height;
    SkipNode<T>** forward;
};

template <typename T>
inline SkipNode<T>::SkipNode(T key, int height) {
    this->key = key;
    this->height = height;

    forward = new SkipNode<T>*[this->height];
}

template <typename T>
inline SkipNode<T>::SkipNode(int height) {
    this->height = height;

    forward = new (SkipNode<T>*)[];

}

template <typename T>
SkipNode<T>::~SkipNode() {
    key = '\0';
    height = 0;
    delete[] forward;
}

#endif
