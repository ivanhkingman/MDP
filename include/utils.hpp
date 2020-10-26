using namespace std;

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <random>

#include "mdp.hpp"


enum actions {UP, DOWN, LEFT, RIGHT};


stateSpace create2DGridWorld(int size);
rewardMap generateRandomRewardMap(stateSpace gridWorld, int low, int high);
transitionMap generateGridWorldTransitionMap(int dim, actionSpace A, stateSpace S);
transitionMap generateZeroTransitionMap(actionSpace A, stateSpace S);
void fillIncompleteTransitionMap(transitionMap &T, actionSpace A, stateSpace S);
// Todo: Add function to verify axioms of probability for transition maps

void printGridWolrd(int dim, state position);
void printRewardMap(rewardMap rewardMap, int dim);

bool isOnUpperEdge(state state, int dim);
bool isOnLeftEdge(state state);
bool isOnLowerEdge(state state);
bool isOnRightEdge(state state, int dim);
bool isOnAnyEdge(state state, int dim);

state getTileBelow(state fromState);
state getTileAbove(state fromState);
state getTileToLeft(state fromState);
state getTileToRight(state fromState);

action flipClockWize(action moveDirection);
action flipCounterClockwize(action moveDirection);
