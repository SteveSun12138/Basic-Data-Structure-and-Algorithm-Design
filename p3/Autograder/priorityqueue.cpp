#include <iostream>
#include "json.hpp"
#include <vector>

#include "priorityqueue.h"

void Swap(KeyValuePair &k1, KeyValuePair &k2){
    KeyValuePair temp;
    temp = k1;
    k1 = k2;
    k2 = temp;
    return;
}

PriorityQueue::PriorityQueue(std::size_t max_size) :
        nodes_(max_size + 1, KeyValuePair()),
        max_size_(max_size),
        size_(0) {
}

void PriorityQueue::insert(Key k) {
    insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
    // TODO: complete this function
    size_++;
    int i = size_;
    if(size_ <= max_size_){
        nodes_[i] = std::make_pair(kv.first, kv.second);
    }
    //up
    while(i > 1){
        heapifyUp(i);
        i = i / 2;
    }

}

KeyValuePair PriorityQueue::min() {
    // TODO: complete this function
    return nodes_[1];

}

KeyValuePair PriorityQueue::removeMin() {

    nodes_[1] = nodes_[size_];
    //size_--;
    nodes_.pop_back();
    size_--;

    int i = 1;
    int temp = 0;
    while ((unsigned)(2 * i) <= size_ || (unsigned)(2 * i + 1) <= size_){
        if((unsigned)(2 * 1 + 1) <= size_){
            if(nodes_[2*i].first < nodes_[2*i + 1].first){
                temp = 2 * i;
            }else{
                temp = 2 * i +1;
            }

        }else {
            temp = 2 * i;
        }
        heapifyDown(i);
        i = temp;
    }


    return nodes_[1];
}

bool PriorityQueue::isEmpty() const {
    //FIXME: i = 1
    if(size_ == 0){
        return true;
    }else{
        return false;
    }
}

size_t PriorityQueue::size() const {
    // TODO: complete this function
//    for(int i = 1; i <= size_; ++i){
//        std::cout << nodes_[i].first << std::endl;
//    }
//    std::cout << "size: " << size_ << std::endl;
//    std::cout << "root: " << nodes_[1].first << std::endl;
//    std::cout << "last element: " << nodes_[size_].first << std::endl;
//
    return size_;
}

nlohmann::json PriorityQueue::JSON() const {
    nlohmann::json result;
    for (size_t i = 1; i <= size_; i++) {
        nlohmann::json node;
        KeyValuePair kv = nodes_[i];
        node["key"] = kv.first;
        node["value"] = kv.second;
        if (i != ROOT) {
            node["parent"] = std::to_string(i / 2);
        }
        if (2 * i <= size_) {
            node["leftChild"] = std::to_string(2 * i);
        }
        if (2 * i + 1 <= size_) {
            node["rightChild"] = std::to_string(2 * i + 1);
        }
        result[std::to_string(i)] = node;
    }
    result["metadata"]["max_size"] = max_size_;
    result["metadata"]["size"] = size_;
    return result;
}

void PriorityQueue::heapifyUp(size_t i) {
    // TODO: complete this function
    KeyValuePair temp;
    //judge whether arrive root node
    if (i > 1) {
        if(nodes_[i].first < nodes_[i/2].first){
            Swap(nodes_[i], nodes_[i/2]);
        }
    }

}

void PriorityQueue::heapifyDown(size_t i) {
    // TODO: complete this function
    KeyValuePair temp;
    //judge whether arrive max size
    //

    if((2*i <= size_ && nodes_[i].first > nodes_[2*i].first)
    ||(2*i + 1 <= size_ && nodes_[i].first > nodes_[2*i + 1].first)){
        if(2*i + 1 <= size_){
            if(nodes_[2*i].first > nodes_[2*i + 1].first){
                Swap(nodes_[i], nodes_[2*i + 1]);
                //i = 2*i + 1;
            }else{
                Swap(nodes_[i], nodes_[2*i]);
                //i = 2*i;
            }
        }else{
            Swap(nodes_[i], nodes_[2*i]);
            //i = 2*i;
        }
    }



}

void PriorityQueue::removeNode(size_t i) {
    // TODO: complete this function

    //size_--;
    nodes_.pop_back();
    size_--;
    //down
    while (2*i <= size_ || 2*i + 1 <= size_){
        heapifyDown(i);
        if(2*i + 1 <= max_size_){
            if(nodes_[2*i].first > nodes_[2*i + 1].first){
                i = 2*i + 1;
            }else{
                i = 2*i;
            }
        } else{
            i = 2*i;
        }
    }
}

Key PriorityQueue::getKey(size_t i) {
    //FIXME: what is key
    return nodes_[i].first;
}
