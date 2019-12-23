//
// Created by Guoqin Sun on 2019-03-15.
//

#ifndef HW4NEW_AVL_H
#define HW4NEW_AVL_H

#include <memory>
#include <string>

class Node {
public:

    Node(int key) :
            key_(key),
            parent_(std::weak_ptr<Node>()),
            left_(nullptr),
            right_(nullptr),
            height(1){}
    Node(int key, std::weak_ptr<Node> parent) :
            key_(key),
            parent_(parent),
            left_(nullptr),
            right_(nullptr),
            height(1){}

    int key_;
    std::weak_ptr<Node> parent_;
    std::shared_ptr<Node> left_;
    std::shared_ptr<Node> right_;
    int height;

};

class AVLTree {
public:
    AVLTree() : root(nullptr), size_(0){}
    std::shared_ptr<Node> root;
    int height(std::shared_ptr<Node> N) const;
    int max(int a, int b);
    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, int key);
    int getBalance(std::shared_ptr<Node> N) const;
    std::shared_ptr<Node> rightRotate(std::shared_ptr<Node> y);
    std::shared_ptr<Node> leftRotate(std::shared_ptr<Node> y);
    void preOrder(std::shared_ptr<Node> node);
    std::string JSON() const;
    size_t size_;
};


#endif //HW4NEW_AVL_H
