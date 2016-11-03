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

class SkipNode {
    friend class SkipList;

    public:
        SkipNode(int key, std::string data, int height);
        SkipNode(int key, int height);
        SkipNode(int height);
        ~SkipNode();
        
        int key;
        std::string data;
        int height;
        SkipNode** fwdNodes;

        
};

inline SkipNode::SkipNode(int key, std::string data, int height) {
    fwdNodes = new SkipNode*[height];
    this->key = key;
    this->data = data;
    this->height = height;
    for (int i = 0; i < height; i++)
        fwdNodes[i] = NULL;
}

inline SkipNode::SkipNode(int key, int height) {
    fwdNodes = new SkipNode*[height];
    this->key = key;
    this->height = height;
    for (int i = 0; i < height; i++)
        fwdNodes[i] = NULL;
}
    

inline SkipNode::SkipNode(int height) {
    fwdNodes = new SkipNode*[height];
    data = "";
    this->height = height;
    for (int i = 0; i < height; i++)
        fwdNodes[i] = NULL;
}

inline SkipNode::~SkipNode() {
    data = '\0';
    key = '\0';
    delete[] fwdNodes;
}


#endif
