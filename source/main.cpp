#include "agent.hpp"
#include "environment.hpp"
#include "algorithm.hpp"
#include "gridworld.hpp"
#include "tests.hpp"
#include "valueiteration.hpp"

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;

int main(){

    srand(time(0));

    // Set parameters of gridWorld
    int dim = 6;
    unsigned int nTurns = 10;

    // Create a grid world
    GridWorld myGridWorld(dim, 0, 10, 0.7);

    // Steal MDP from gridworld
    MDP myMDP = myGridWorld.stealMdp();

    // Create an agent and deploy it in grid world
    Agent myAgent;
    myAgent.setMDP(myMDP);
    myAgent.deployInEnvironment(myGridWorld);

    // Create algorithm and attatch it to agent
    ValueIteration valueIteration(myMDP, 0.5, 0.001);
    valueIteration.setOwner(myAgent);

    // Run algorithm
    displayValueGrid(myAgent.getValueMap());
    valueIteration.run();
    valueIteration.derivePolicyFromValueMap();


    // Let agent play

    int turns = 0;
    int maxTurns = 25;
    while (turns < maxTurns) {
        myAgent.observeState();
        state currentState = myAgent.getStateEstimate();
        action nextAction = myAgent.getPolicy().at(currentState);
        myAgent.executeAction(nextAction);
        myAgent.observeState();
        myAgent.collectReward();
        turns++;
    }

    
    cout << "Agent played on map: " << endl; myGridWorld.displayRewardMap();
    
    int PCreward = myAgent.getReward();
    
    // Let user play
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
    cout << "Algorithm accumulated reward: " << PCreward;

    cout << "Agent thought tiles had these values: " << endl; displayValueGrid(myAgent.getValueMap());
    cout << "Agent played with policy: " << endl; displayPolicyGrid(myAgent.getPolicy());
    

    return 0;
}