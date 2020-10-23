#include "utils.hpp"

set<vector<int>> create2DGridWorld(int size) {

    set<vector<int>> gridWorld;
    vector<int> position;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y< size; y++) {
            position = {x,y};
            gridWorld.insert(position);
        }
    }
    
    return gridWorld;  
}

void printGridWolrd(int dim, vector<int> position) {
    for (int x = 0;  x < dim; x++ ) {
        for (int y = 0; y < dim; y++) {
            vector<int> tile {x,y};
            if (tile == position) {
                cout << "[x]";
            }
            else
                cout << "[ ]";
        }
        cout << endl;
    }
}

map<vector<int>, int> generateRandomRewardMap(set<vector<int>> gridWorld, int low, int high) {
    map<vector<int>, int> rewardMap;
    for (auto it = gridWorld.begin(); it != gridWorld.end(); it++) {
        int randomReward = rand() % high + low;
        rewardMap.insert(pair<vector<int>, int>(*it, randomReward));
    }
    return rewardMap;
}

void printRewardMap(map<vector<int>, int> rewardMap, int dim) {
    for (int x = 0;  x < dim; x++ ) {
        for (int y = 0; y < dim; y++) {
            vector<int> tile {x,y};
            cout << "[" << rewardMap[tile] << "]";
        }
        cout << endl;
    }
}