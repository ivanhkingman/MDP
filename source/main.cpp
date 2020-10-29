#include "agent.hpp"
#include "environment.hpp"
#include "algorithm.hpp"
#include "gridworld.hpp"
#include "tests.hpp"
#include "valueiteration.hpp"

#include <iostream>
#include <unistd.h>

using namespace std;

int main(){

    // Set parameters of gridWorld
    int dim = 5;
    int moves = 10;

    // Create a grid world
    GridWorld myGridWorld(dim, 0, 10, 0.6);
    myGridWorld.displayGridWorld();

    // Steal MDP from gridworld
    MDP myMDP = myGridWorld.stealMdp();

    // Create an agent
    Agent myAgent;
    myAgent.setMDP(myMDP);
    myAgent.deployInEnvironment(myGridWorld);

    // Create algorithm
    ValueIteration valueIteration;
    myAgent.attatchAlgorithm(valueIteration);
    

    // Let player play the game using human intelligence.
    // letUserPlayGridWorld(myAgent, myMDP, dim, moves, successRate);

    // cout << "Playing on map: " << endl;
    // displayRewardMap(myRewardMap, dim);

    // Let computer play the game using valueiteration
    // letAlgorithmPlayGridWorld(myAgent, myMDP, dim, moves, 0.8, successRate);

    /* Let computer play the game using policy iteration
    policy agentPolicy = policyIteration(myMDP, 0.5, 0.001);
    for (int turn = 0; turn < moves; turn++) {
        action nextMove = agentPolicy.at(myAgent.getPosition());
        myAgent.executeAction(nextMove);
        myAgent.collectReward();

    }

    double agentReward = myAgent.getReward();
    cout << "Policy iteration algorithm accumulated reward: " << myAgent.getReward() << endl;
    cout << "Agent used policy: " << endl;
    myAgent.displayPolicy(agentPolicy, dim);
    myAgent.reset();

    stateActionValueMap Q = zeroInitializeQ(myStateSpace, myActionSpace);
    printStateActionValueMap(Q); cout << endl;
    */

    return 0;
}