#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>


nlohmann::json read_jsonFile(std::string jsonFile_name);
//void readSamples(std::vector<std::string>& SampleList, nlohmann::json file1);
void GetAll(nlohmann::json jsonFile, std::vector<std::string> &index,
            std::vector<Key> &key, PriorityQueue &queue);
void InsertHeap(nlohmann::json jsonFile, std::vector<std::string> &index,
                std::vector<Key> &key, PriorityQueue &queue);
void CreateNewJson(nlohmann::json jsonFile, std::vector<std::string> &index,
                   std::vector<Key> &key, nlohmann::json &new_json, PriorityQueue &queue);
int main(int argc, char** argv) {

    std::vector<std::string> index;
    std::vector<Key> key;
    nlohmann::json new_json;
    KeyValuePair heap;

    //read json file
    nlohmann::json jsonFile = read_jsonFile(argv[1]);

    int maxSize = jsonFile["metadata"]["maxHeapSize"];
    PriorityQueue queue(maxSize);

    GetAll(jsonFile, index, key, queue);

    InsertHeap(jsonFile, index, key, queue);
//
    CreateNewJson(jsonFile, index, key, new_json, queue);


    return 0;
}


nlohmann::json read_jsonFile(std::string jsonFile_name) {
    std::ifstream file;
    file.open(jsonFile_name);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
        return jsonObject;
    }else{
        std::cerr << "Error." << std::endl;
    }
    return 0;
}

void GetAll(nlohmann::json jsonFile, std::vector<std::string> &index,
            std::vector<Key> &key, PriorityQueue &queue) {
    if (jsonFile["metadata"]["numOperations"] >= 100) {
        for (int i = 1; i < 10; ++i) {
            std::string temp = "Op00";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 10; i <= 99; ++i) {
            std::string temp = "Op0";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 100; i <= jsonFile["metadata"]["numOperations"]; ++i) {
            std::string temp = "Op";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
    } else if (jsonFile["metadata"]["numOperations"] >= 10 &&
               jsonFile["metadata"]["numOperations"] <= 99) {
        for (int i = 1; i < 10; ++i) {
            std::string temp = "Op00";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 10; i <= jsonFile["metadata"]["numOperations"]; ++i) {
            std::string temp = "Op0";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
    } else if (jsonFile["metadata"]["numOperations"] < 10) {
        for (int i = 1; i < 10; ++i) {
            std::string temp = "Op0";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
    }

    return;
}


void InsertHeap(nlohmann::json jsonFile, std::vector<std::string> &index,
                std::vector<Key> &key, PriorityQueue &queue){
    int size = jsonFile["metadata"]["numOperations"];
    //std::cout << "size: " << size << std::endl;

    for (int i = 0; i < size; ++i) {
        if(jsonFile[index[i]]["operation"] == "insert"){
            double a = jsonFile[index[i]]["key"];
            if(queue.size() < jsonFile["metadata"]["maxHeapSize"]){
                queue.insert(a);
            }
        } else {
            queue.removeMin();
        }

    }
}

void CreateNewJson(nlohmann::json jsonFile, std::vector<std::string> &index,
                   std::vector<Key> &key, nlohmann::json &new_json, PriorityQueue &queue){
    new_json = queue.JSON();
    new_json["metadata"]["maxHeapSize"] = jsonFile["metadata"]["maxHeapSize"];
    new_json["metadata"]["numOperations"] = jsonFile["metadata"]["numOperations"];

    std::cout << new_json.dump(2) << std::endl;
    exit(0);

}
