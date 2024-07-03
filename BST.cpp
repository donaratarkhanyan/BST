#include "BST.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
BST<T>::BST()
    : root{nullptr}
{}

template <typename T>
BST<T>::~BST() {
    clear(root);
}

template <typename T>
typename BST<T>::Node* BST<T>::insertHelper(Node*& node, T value) {
    if (!node) {
        return new Node(value);
    }
    if (node->val > value) {
        node->left = insertHelper(node->left, value);
    } else if (node->val < value) {
        node->right = insertHelper(node->right, value);
    }
    return node;
}

template <typename T>
void BST<T>::insert(T value) {
    root = insertHelper(root, value);
}

template <typename T>
typename BST<T>::Node* BST<T>::searchHelper(Node* node, T value) const {
    if (!node) {
        return nullptr;
    }
    if (node->val == value) {
        return node;
    } else if (node->val > value) {
        return searchHelper(node->left, value);
    } else {
        return searchHelper(node->right, value);
    }
}

template <typename T>
bool BST<T>::search(T value) const {
    return searchHelper(root, value) != nullptr;
}

template <typename T>
void BST<T>::preorderHelper(Node* node) const {
    if (!node) {
        return;
    }
    std::cout << node->val << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
}

template <typename T>
void BST<T>::preorder() const {
    preorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::inorderHelper(Node* node) const {
    if (!node) {
        return;
    }
    inorderHelper(node->left);
    std::cout << node->val << " ";
    inorderHelper(node->right);
}

template <typename T>
void BST<T>::inorder() const {
    inorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::postorderHelper(Node* node) const {
    if (!node) {
        return;
    }
    postorderHelper(node->left);
    postorderHelper(node->right);
    std::cout << node->val << " ";
}

template <typename T>
void BST<T>::postorder() const {
    postorderHelper(root);
    std::cout << std::endl;
}

template <typename T>
void BST<T>::clear(Node* node) {
    if (!node) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
typename BST<T>::Node* BST<T>::deleteValueHelper(Node* node, T value) {
    if (!node) {
        return nullptr;
    }
    if (node->val > value) {
        node->left = deleteValueHelper(node->left, value);
    } else if (node->val < value) {
        node->right = deleteValueHelper(node->right, value);
    } else {
        if (!node->left) {
            Node* rightNode = node->right;
            delete node;
            return rightNode;
        } else if (!node->right) {
            Node* leftNode = node->left;
            delete node;
            return leftNode;
        } else {
            Node* tmp = getMin(node->right);
            node->val = tmp->val;
            node->right = deleteValueHelper(node->right, tmp->val);
        }
    }
    return node;
}

template <typename T>
void BST<T>::deleteValue(T value) {
    root = deleteValueHelper(root, value);
}

template <typename T>
typename BST<T>::Node* BST<T>::getMin(Node* node) const {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::getMax(Node* node) const {
    while (node->right) {
        node = node->right;
    }
    return node;
}

template <typename T>
int BST<T>::getHeightHelper(Node* node) const {
    if (!node) {
        return 0;
    }
    return std::max(getHeightHelper(node->left), getHeightHelper(node->right)) + 1;
}

template <typename T>
int BST<T>::getHeight() const {
    return getHeightHelper(root);
}

template <typename T>
int BST<T>::getSizeHelper(Node* node) const {
    if (!node) {
        return 0;
    }
    return getSizeHelper(node->left) + getSizeHelper(node->right) + 1;
}

template <typename T>
int BST<T>::getSize() const {
    return getSizeHelper(root);
}

template <typename T>
typename BST<T>::Node* BST<T>::getPredecessorHelper(Node* node, T value) const {
    if (!node) {
        return nullptr;
    }
    if (node->left) {
        return getMax(node->left);
    }
    Node* ancestor = root;
    Node* predecessor = nullptr;
    while (ancestor != node) {
        if (ancestor->val < node->val) {
            predecessor = ancestor;
            ancestor = ancestor->right;
        } else {
            ancestor = ancestor->left;
        }
    }
    return predecessor;
}

template <typename T>
T BST<T>::getPredecessor(T value) const {
    Node* tmp = searchHelper(root, value);
    Node* node = getPredecessorHelper(tmp, value);
    if (!node) {
        throw std::invalid_argument("The value is the first element.");
    }
    return node->val;
}

template <typename T>
typename BST<T>::Node* BST<T>::getSuccessorHelper(Node* node, T value) const {
    if (!node) {
        return nullptr;
    }
    if (node->right) {
        return getMin(node->right);
    }
    Node* ancestor = root;
    Node* successor = nullptr;
    while (ancestor != node) {
        if (ancestor->val > node->val) {
            successor = ancestor;
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }
    return successor;
}

template <typename T>
T BST<T>::getSuccessor(T value) const {
    Node* tmp = searchHelper(root, value);
    Node* node = getSuccessorHelper(tmp, value);
    if (!node) {
        throw std::invalid_argument("The value is the last element.");
    }
    return node->val;
}
