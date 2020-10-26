#include <iostream>
#include "utils.hpp"
// #include "mdp.hpp"


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

    // Create and set transitions for the agent
    transitionMap myTransitionMap = generateZeroTransitionMap(myActionSpace, myStateSpace);
    myMDP.setTransitionMap(myTransitionMap);
    
    myMDP.printTransitionMap();
    
    return 0;
}