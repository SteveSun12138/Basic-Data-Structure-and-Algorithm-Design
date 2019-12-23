#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include <vector>
#include <fstream>
#include <utility>

nlohmann::json read_jsonFile(std::string jsonFile_name);

int main(int argc, char** argv) {

    nlohmann::json jsonFile = read_jsonFile(argv[1]);

    nlohmann::json Object;

    Key key;
    std::vector<double> ki;
    std::vector<Key> Keys;
    std::vector<int> playerOne;
    std::vector<int> playerTwo;
    std::vector<Value> teams; //pairs of values
    std::vector<KeyValuePair> keyvalue_pairs; //pairs of KeyValuePair

    //input json file
    for (auto arrayItr = jsonFile["teamStats"].begin(); arrayItr != jsonFile["teamStats"].end(); ++arrayItr) {
        Object = *arrayItr;
        ki.push_back(Object["winPercentage"]);
        playerOne.push_back(Object["playerOne"]);
        playerTwo.push_back(Object["playerTwo"]);
    }

    //values
    for (int j = 0; (unsigned)j < playerOne.size(); ++j) {
        std::pair<int, int> team;
        team.first = playerOne[j];
        team.second = playerTwo[j] ;
        teams.push_back(team);
    }

    //keys
    for (int i = 0; (unsigned)i < ki.size(); ++i) {
        key = fabs(ki[i] - 50);
        Keys.push_back(key);
    }

    //keyvaluePairs
    for (int k = 0; (unsigned)k < Keys.size(); ++k) {
        keyvalue_pairs.emplace_back(std::make_pair(Keys[k], teams[k]));
    }

    PriorityQueue queue(Keys.size());

    std::vector<Value> bestTeams;
    std::vector<Value> resultTeams;
    std::vector<int> teamsMember_one;
    std::vector<int> teamsMember_two;
    int teamMember = jsonFile["metadata"]["numPlayers"];

    for (int l = 0; (unsigned)l < keyvalue_pairs.size(); ++l) {
        queue.insert(keyvalue_pairs[l]);

    }


    for (int m = 0; (unsigned)m < keyvalue_pairs.size(); ++m) {
        bestTeams.push_back(queue.min().second);
        queue.removeMin();
    }

    //remove duplicate elements
    int arr1[teamMember];
    for (int k1 = 0; k1 < teamMember; ++k1) {
        arr1[k1] = 0;
    }

    for (int l1 = 0; (unsigned)l1 < bestTeams.size(); ++l1) {
        if (arr1[bestTeams[l1].first] == 0 && arr1[bestTeams[l1].second] == 0){
            resultTeams.push_back(std::make_pair(bestTeams[l1].first, bestTeams[l1].second));
            arr1[bestTeams[l1].first]++;
            arr1[bestTeams[l1].second]++;
        }
    }

//  for (int i1 = 0; i1 < resultTeams.size(); ++i1) {
//    std::cout << resultTeams[i1].first << ", "<< resultTeams[i1].second << "\n";
//  }


    nlohmann::json output_Json;
    output_Json["teams"] = resultTeams;
    std::cout << output_Json.dump(2);

    return 0;
}


nlohmann::json read_jsonFile(std::string jsonFile_name) {
    std::ifstream file;
    file.open(jsonFile_name);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
        return jsonObject;
    }
    return 0;
}

