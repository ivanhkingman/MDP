using namespace std;

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <random>

#include "mdp.hpp"

stateSpace create2DGridWorld(int size);
rewardMap generateRandomRewardMap(stateSpace gridWorld, int low, int high);
transitionMap generateGridWorldTransitionMap(int dim, actionSpace A, stateSpace S);
transitionMap generateZeroTransitionMap(actionSpace A, stateSpace S);

void printGridWolrd(int dim, vector<int> position);
void printRewardMap(map<vector<int>, int> rewardMap, int dim);

bool isOnUpperEdge(state state, stateSpace S, int dim);
