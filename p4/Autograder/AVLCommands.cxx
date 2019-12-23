#include <iostream>
#include "AVL.h"
//#include "BST.h"

#include "json.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <utility>

nlohmann::json read_jsonFile(std::string js);

void Insertion(nlohmann::json jsonFile,
        std::vector<std::string>& index, AVLTree &tree);

void CreateNewJson(nlohmann::json jsonFile,
        std::vector<std::string>& index, AVLTree &tree, nlohmann::json &new_json);

int main(int argc, char** argv) {

    std::vector<std::string> index;
    AVLTree tree;
    nlohmann::json new_json;
    //BSTNode bstNode();

    nlohmann::json jsonFile = read_jsonFile(argv[1]);
    // insert and delete all keys into bst mode
    Insertion(jsonFile, index, tree);

    //assign value to new json
    CreateNewJson(jsonFile, index, tree, new_json);
    //print it out

    return 0;
}

void Insertion(nlohmann::json jsonFile,
               std::vector<std::string>& index, AVLTree &tree) {
    // read numbers from json
    int size = jsonFile["metadata"]["numOps"];
    // case 1: numops = 10
    if(size >= 10 && size < 1000) {
        for (int i = 0; i < 10; ++i) {
            std::string temp = "0";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 10; i <= size; ++i) {
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            index.push_back(str1);
        }
    }
    // case 2: numops = 1000
    if (size >= 1000) {
        for (int i = 0; i < 10; ++i) {
            std::string temp = "000";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 10; i < 100; ++i) {
            std::string temp = "00";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 100; i < 1000; ++i) {
            std::string temp = "0";
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            temp += str1;
            index.push_back(temp);
        }
        for (int i = 1000; i <= size; ++i) {
            std::stringstream sss;
            sss << i;
            std::string str1 = sss.str();
            index.push_back(str1);
        }
    }

    // do insertion
    // insert one, check from it to above to see |bf| <= 1
    // if true, keep rotating
    // until the whole |bf| <= 1
    for (int j = 1; j <= size; ++j) {
        if(jsonFile[index[j]]["operation"] == "Insert"){
            tree.root = tree.insert(tree.root, jsonFile[index[j]]["key"]);
        }
    }

}

void CreateNewJson(nlohmann::json jsonFile,
        std::vector<std::string>& index, AVLTree &tree, nlohmann::json &new_json) {
    std::cout << tree.JSON() << '\n';
}

nlohmann::json read_jsonFile(std::string js) {
    std::ifstream file;
    file.open(js);
    nlohmann::json json;
    if(file.is_open()){
        file >> json;
        return json;
    } else{
        std::cerr << "Error." << std::endl;
    }

    return 0;
}