#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
class BST {
private:
    struct Node {
        T val;
        Node* left;
        Node* right;

        Node(T val) 
            : val(val) 
            , left(nullptr) 
            , right(nullptr) 
        {}
    };

    Node* root;

    Node* insertHelper(Node*& node, T value);
    Node* searchHelper(Node* node, T value) const;
    void preorderHelper(Node* node) const;
    void inorderHelper(Node* node) const;
    void postorderHelper(Node* node) const;
    void clear(Node* node);
    Node* deleteValueHelper(Node* node, T value);
    Node* getMin(Node* node) const;
    Node* getMax(Node* node) const;
    int getHeightHelper(Node* node) const;
    int getSizeHelper(Node* node) const;
    Node* getPredecessorHelper(Node* node, T value) const;
    Node* getSuccessorHelper(Node* node, T value) const;
public:
    BST();
    ~BST();
    
    void insert(T value);
    bool search(T value) const;
    void inorder() const;
    void preorder() const;
    void postorder() const;
    void deleteValue(T value);
    int getHeight() const;
    int getSize() const;
    T getPredecessor(T value) const;
    T getSuccessor(T value) const;
};

#include "BST.cpp"
#endif // BST_H