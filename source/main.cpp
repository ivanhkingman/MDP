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

    
    // Create and set up transition matrix for the MDP
    transitionMap myTransitionMap;
    for (auto fromState = myStateSpace.begin(); fromState != myStateSpace.end(); fromState++) {
        for (auto toState = myStateSpace.begin(); toState != myStateSpace.end(); toState++) {
            for (auto withAction = myActionSpace.begin(); withAction != myActionSpace.end(); withAction++) {
                transition currentTransition {*fromState, *toState, *withAction};
                // myTransitionMap.insert(pair<transition, probability>(currentTransition, 0));
            }
        }
    }
    
    
    state st1 = {1,2};
    state st2 = {0,0};
    action a = UP;
    transition myTransition = {st1, st2, a};

    myMDP.printActionSpace();
    
    return 0;
}