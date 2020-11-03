#include "agent.hpp"
#include "environment.hpp"
#include "algorithm.hpp"
#include "gridworld.hpp"
#include "tests.hpp"
#include "valueiteration.hpp"
#include "policyiteration.hpp"
#include "qlearning.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;

int main(){

    srand(time(0));

    // Set parameters of gridWorld
    int dim = 3;
    unsigned int nTurns = 10;
    int PCReward = 0;
    int turns;

    // Create a grid world
    GridWorld myGridWorld(dim, 0, 10, 0.8);
    myGridWorld.displayRewardMap();

    // Steal MDP from gridworld
    MDP myMDP = myGridWorld.stealMdp();

    // Create an agent and deploy it in grid world
    Agent myAgent;
    myAgent.setMDP(myMDP);
    myAgent.deployInEnvironment(myGridWorld);

    stateSpace S = myMDP.getStateSpace();
    actionSpace A = myMDP.getActionSpace();

    // Create algorithm: Q-learning
    QLearning qLearning(S, A, true, 100, 0.1, 0.5, 0.1, 10);
    qLearning.setOwner(myAgent);
    qLearning.run();

    myAgent.reset();
    myGridWorld.reset();
    
    // Let Q-learning agent play
    turns = 0;
    int maxTurns = 10;
    while (turns < nTurns) {
        myAgent.observeState();
        state currentState = myAgent.getStateEstimate();
        action nextAction = myAgent.getPolicy().at(currentState);
        myAgent.executeAction(nextAction);
        myAgent.observeState();
        myAgent.collectReward();
        turns++;
    };
    
    PCReward = myAgent.getReward();
    cout << "Q-learning accumulated reward: " << PCReward << endl;
    // cout << "Agent thought tiles had these values: " << endl; displayValueGrid(myAgent.getValueMap());
    cout << "Agent played with policy: " << endl; displayPolicyGrid(myAgent.getPolicy());

    myAgent.reset();
    myGridWorld.reset();

    // Let Value-iteration play
    ValueIteration valueIteration(myMDP, 0.1, 0.001);
    valueIteration.setOwner(myAgent);
    valueIteration.run();

    // Let Q-learning agent play
    turns = 0;
    while (turns < nTurns) {
        myAgent.observeState();
        state currentState = myAgent.getStateEstimate();
        action nextAction = myAgent.getPolicy().at(currentState);
        myAgent.executeAction(nextAction);
        myAgent.observeState();
        myAgent.collectReward();
        turns++;
    };
    
    PCReward = myAgent.getReward();
    cout << "Value iteration accumulated reward: " << PCReward << endl;
    // cout << "Agent thought tiles had these values: " << endl; displayValueGrid(myAgent.getValueMap());
    cout << "Agent played with policy: " << endl; displayPolicyGrid(myAgent.getPolicy());

    myAgent.reset();
    myGridWorld.reset();
    
    // Let user play

    /*
    cout << endl << "Can you beat the computer?" << endl;
    myGridWorld.reset();

    myGridWorld.display();
    cout << "=================" << endl;
    myGridWorld.displayRewardMap();
    
    Agent user;
    user.setMDP(myMDP);
    user.deployInEnvironment(myGridWorld);
    user.observeState(); // Rename to observe environment?

    
    int turnCounter = 0;
    while(turnCounter < maxTurns) {
        string userInput;
        cin >> userInput;
        if (userInput == "w") {
            user.executeAction(UP);
        }
        if (userInput == "s") {
            user.executeAction(DOWN);
        }
        if (userInput == "a") {
            user.executeAction(LEFT);
        }
        if (userInput == "d") {
            turnCounter++;
            userInput = "_";
            user.executeAction(RIGHT);
        }
        if (userInput == "e") {
            break;
        }
        processTurn(turnCounter, userInput, user, myGridWorld);
    }
    double agentReward = user.getReward();
    cout << "You accumulated reward: " << user.getReward() << endl;
    cout << "Algorithm accumulated reward: " << PCReward; cout << endl;

    cout << "Agent thought tiles had these values: " << endl; displayValueGrid(myAgent.getValueMap());
    cout << "Agent played with policy: " << endl; displayPolicyGrid(myAgent.getPolicy());
    
    */

    return 0;
}