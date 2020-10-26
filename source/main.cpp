#include <iostream>
#include "utils.hpp"
// #include "agent.hpp"
// #include "mdp.hpp"


using namespace std;

int main(){

    // Create MDP
    MDP myMDP;

    // Create and set state space, i.e. possible states for the agent and environment
    stateSpace myStateSpace = create2DGridWorld(5);
    myMDP.setStateSpace(myStateSpace);

    // Create and set reward map, i.e. immediate rewards associated with states
    rewardMap myRewardMap = generateRandomRewardMap(myStateSpace, -100, 100);
    myMDP.setRewardMap(myRewardMap);

    // Create and set actions for the agent
    
    actionSpace myActionSpace = {actions::UP, actions::DOWN, actions::LEFT, actions::RIGHT};
    myMDP.setActionSpace(myActionSpace);

    // Create and set transitions for the agent
    transitionMap myTransitionMap = generateGridWorldTransitionMap(4, myActionSpace, myStateSpace);
    myMDP.setTransitionMap(myTransitionMap);
    
    // Agent myAgent;
    for (int i = 0; i < 100; i++) {
        int dice = rand() % 10 + 1;
        cout << dice << endl;
    }
    

    return 0;
}