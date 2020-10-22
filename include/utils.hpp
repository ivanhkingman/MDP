using namespace std;

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <random>


set<vector<int>> create2DGridWorld(int size);
map<vector<int>, int> generateRandomRewardMap(set<vector<int>> gridWorld, int low, int high);

void printGridWolrd(int dim, vector<int> position);
void printRewardMap(map<vector<int>, int> rewardMap, int dim);
