#include <iostream>
#include <unistd.h>


#include "agent.hpp"
#include "algorithms.hpp"
#include "tests.hpp"

using namespace std;

int main(){

    // Set parameters of gridWorld
    int dim = 5;
    double successRate = 0.6;
    int moves = 10;

    // Create MDP
    MDP myMDP;

    // Create and set state space, i.e. possible states for the agent and environment
    stateSpace myStateSpace = create2DGridWorld(dim);
    myMDP.setStateSpace(myStateSpace);

    // Create and set reward map, i.e. immediate rewards associated with states
    rewardMap myRewardMap = generateRandomRewardMap(myStateSpace, 0, 10);
    myMDP.setRewardMap(myRewardMap);

    // Create and set actions for the agent
    actionSpace myActionSpace = {actions::UP, actions::DOWN, actions::LEFT, actions::RIGHT};
    myMDP.setActionSpace(myActionSpace);

    // Create and set transitions for the agent
    transitionMap myTransitionMap = generateGridWorldTransitionMap(6, myActionSpace, myStateSpace, successRate);
    myMDP.setTransitionMap(myTransitionMap);

    // Create an agent
    Agent myAgent;
    myAgent.setMDP(myMDP);

    // Let player play the game using human intelligence. How sad.
    // letUserPlayGridWorld(myAgent, myMDP, dim, moves, successRate);

    cout << "Playing on map: " << endl;
    displayRewardMap(myRewardMap, dim);

    // Let computer play the game using valueiteration
    letAlgorithmPlayGridWorld(myAgent, myMDP, dim, moves, 0.8, successRate);

    // Let computer play the game using policy iteration
    policy agentPolicy = policyIteration(myMDP, 0.5, 0.001);
    for (int turn = 0; turn < moves; turn++) {
        action nextMove = agentPolicy.at(myAgent.getPosition());
        myAgent.attemptMove(nextMove, successRate, dim);
        myAgent.collectReward();
    }

    double agentReward = myAgent.getReward();
    cout << "Policy iteration algorithm accumulated reward: " << myAgent.getReward() << endl;
    cout << "Agent used policy: " << endl;
    displayPolicy(agentPolicy, dim);
    myAgent.reset();

    stateActionValueMap Q = zeroInitializeQ(myStateSpace, myActionSpace);
    printStateActionValueMap(Q); cout << endl;

    return 0;
}