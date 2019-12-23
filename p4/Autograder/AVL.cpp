//
// Created by Guoqin Sun on 2019-03-15.
//

#include "AVL.h"
#include "json.hpp"
#include <iostream>
#include <cassert>
#include <iostream>
#include <string>
#include <queue>



std::shared_ptr<Node> AVLTree::rightRotate(std::shared_ptr<Node> y){
    std::shared_ptr<Node> x = y->left_;
    std::shared_ptr<Node> T2 = x->right_;
    x->right_ = y;
    y->parent_ = x;
    y->left_ = T2;

    y->height = max(height(y->left_), height(y->right_)) + 1;
    x->height = max(height(x->left_), height(x->right_)) + 1;

    //x = y->parent_.lock();
    //y->parent_.lock()->left_ =

    return x;
}

std::shared_ptr<Node> AVLTree::leftRotate(std::shared_ptr<Node> x){
    std::shared_ptr<Node> y = x->right_;
    std::shared_ptr<Node> T2 = y->left_;
    y->left_ = x;
    x->parent_ = y;
    x->right_ = T2;

    x->height = max(height(x->left_), height(x->right_)) + 1;
    y->height = max(height(y->left_), height(y->right_)) + 1;

    //y = x->parent_.lock();

    return y;
}

int AVLTree::height(std::shared_ptr<Node> N) const{
    if (N == nullptr)
        return 0;

    return N->height;
}

int AVLTree::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::getBalance(std::shared_ptr<Node> N) const{
    if (N->left_ == nullptr && N->right_ == nullptr)
        return 0;

    return height(N->right_) - height(N->left_);
}

std::shared_ptr<Node> AVLTree::insert(std::shared_ptr<Node> node, int key_) {

    if (node == nullptr) {
        size_++;
        return std::make_shared<Node>(key_);
    }


    if (key_ < node->key_) {
        //node->left_ = std::make_shared<Node>(key_, node);
        node->left_ = insert(node->left_, key_);
    } else if (key_ > node->key_) {
        //node->right_ = std::make_shared<Node>(key_, node);
        node->right_ = insert(node->right_, key_);
    } else {
        //size_++;
        return node;
    }
//////////////////////////////////////////////////////
    //std::shared_ptr<Node> node =
    node->height = 1 + max(height(node->left_),
                          height(node->right_));

    int balance = getBalance(node);
    //left left
    if (balance < -1 && key_ < node->left_->key_)
        return rightRotate(node);
    //right right
    if (balance > 1 && key_ > node->right_->key_)
        return leftRotate(node);
    //left right
    if (balance < -1 && key_ > node->left_->key_)
    {
        node->left_ = leftRotate(node->left_);
        return rightRotate(node);
    }
    //right left
    if (balance > 1 && key_ < node->right_->key_)
    {
        node->right_ = rightRotate(node->right_);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::preOrder(std::shared_ptr<Node> node)
{
    if (node != nullptr)
    {
        std::cout << node->key_ << " " << std::endl;
        preOrder(node->left_);
        preOrder(node->right_);
    }
    //std::cout << "size: " << size_ << std::endl;
}

std::string AVLTree::JSON() const {

    nlohmann::json result;
    std::queue< std::shared_ptr<Node> > nodes;
    if (root != nullptr) {
        result["root"] = root->key_;
        nodes.push(root);
        while (!nodes.empty()) {
            auto v = nodes.front();
            nodes.pop();
            std::string key_ = std::to_string(v->key_);
            //int temp = getBalance(v);
            result[key_]["balance factor"] = getBalance(v);
            result[key_]["height"] = v->height - 1;

            //std::cout << v->parent_.lock()->key_;

            if (v->left_ != nullptr) {
                result[key_]["left"] = v->left_->key_;
                nodes.push(v->left_);
            }
            if (v->right_ != nullptr) {
                result[key_]["right"] = v->right_->key_;
                nodes.push(v->right_);
            }
            if (v->parent_.lock() != nullptr) {
                result[key_]["parent"] = v->parent_.lock()->key_;

            } else {
                result[key_]["root"] = true;
            }
        }
    }

    result["height"] = root->height - 1;
    result["root"] = root->key_;
    result["size"] = size_;

    return result.dump(2) + "\n";
}

