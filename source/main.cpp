#include <iostream>
#include "agent.hpp"

using namespace std;

int main(){

    // Create MDP
    MDP myMDP;

    // Create and set state space, i.e. possible states for the agent and environment
    stateSpace myStateSpace = create2DGridWorld(4);
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

    // Create an agent
    Agent myAgent;
    myAgent.setMDP(myMDP);
    myAgent.printPosition();

    while(1) {
        string userInput;
        cin >> userInput;
        if (userInput == "w") {
            userInput = "_";
            myAgent.attemptMove(UP);
            myAgent.printPosition();
        }
        if (userInput == "s") {
            userInput = "_";
            myAgent.attemptMove(DOWN);
            myAgent.printPosition();
        }
        if (userInput == "a") {
            userInput = "_";
            myAgent.attemptMove(LEFT);
            myAgent.printPosition();
        }
        if (userInput == "d") {
            userInput = "_";
            myAgent.attemptMove(RIGHT);
            myAgent.printPosition();
        }
        if (userInput == "e") {
            break;
        }
    }
    
    

    return 0;
}