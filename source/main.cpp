#include <iostream>
#include "utils.hpp"
#include "mdp.hpp"


using namespace std;

int main(){

    // Create MDP
    MDP myMDP;

    // Create and set state space, i.e. possible states for the agent and environment
    stateSpace myStateSpace = create2DGridWorld(4);
    myMDP.setStateSpace(myStateSpace);

    // Create and set reward map, i.e. immediate rewards associated with states
    rewardMap myRewardMap = generateRandomRewardMap(myStateSpace, -5, 10);
    myMDP.setRewardMap(myRewardMap);

    // Create and set actions for the agent
    enum actions {UP, DOWN, LEFT, RIGHT};
    actionSpace myActionSpace = {UP, DOWN, LEFT, RIGHT};
    myMDP.setActionSpace(myActionSpace);

    state st1 = {0, 0};
    state st2 = {1, 2};
    action a1 = UP;
    action a2 = DOWN;

    Transition transition1(st1, st2, a1);
    Transition transition2(st2, st1, a2);

    transitionMap myMap;
    myMap.insert(pair<Transition, double>(transition1, 0.5));
    myMap.insert(pair<Transition, double>(transition2, 0.4));

    myMDP.setTransitionMap(myMap);
    myMDP.printTransitionMap();
    
    return 0;
}