/*
* SkipNode.h
*
* author: Jack Fletcher
* date: 10/23/2016
*
* This is a node class used to build a skip list.  The data the node stores
* is integer data (currently) but can be rewritten to store any type of data
* if it was to be used for a different tree.
*
*/
#ifndef SKIP_LIST_NODE_H
#define SKIP_LIST_NODE_H

template <typename T> class SkipList;

template <typename T>
class SkipNode {
    friend class SkipList<T>;

    public:
        inline SkipNode(T key, int height);
        inline SkipNode(int height);
        inline ~SkipNode();
        
        T key;
        int height;
        SkipNode<T>** fwdNodes;
};

template <typename T>
inline SkipNode<T>::SkipNode(T key, int height) {
    fwdNodes = new SkipNode<T>*[height];
    this->key = key;
    this->height = height;
    for (int i = 0; i < height; i++)
        fwdNodes[i] = NULL;
}

template <typename T>
inline SkipNode<T>::SkipNode(int height) {
    fwdNodes = new SkipNode<T>*[height];
    this->height = height;
    for (int i = 0; i < height; i++)
        fwdNodes[i] = NULL;
}

template <typename T>
inline SkipNode<T>::~SkipNode() {
    key = '\0';
    delete[] fwdNodes;
}


#endif
