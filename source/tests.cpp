#include "tests.hpp"

#include <iostream>

/*
void letUserPlayGridWorld(GridWorld gridWorld, int nTurns) {
    gridWorld.displayRewardMap();
    gridWorld.display();

    Agent user;
    MDP mdp = gridWorld.stealMdp();
    user.setMDP(mdp);

    user.deployInEnvironment(gridWorld);

    int turnCounter = 0;
    while(turnCounter < nTurns) {
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
        processTurn(turnCounter, userInput, user, gridWorld);
    }
    double agentReward = user.getReward();
    cout << "You accumulated reward: " << user.getReward() << endl;
}
*/



void letAgentPlayGridWorld(Agent myAgent, GridWorld gridWorld, int maxTurns) {
    int turns = 0;
    while (turns < maxTurns) {
        myAgent.observeState();
        state currentState = myAgent.getStateEstimate();
        action nextAction = myAgent.getPolicy().at(currentState);
        myAgent.executeAction(nextAction);
        myAgent.observeState();
        myAgent.collectReward();
        cout << "Agent state-estimate: " << endl;
        printState(myAgent.getStateEstimate()); cout << endl;
        cout << "Real state: " << endl;
        printState(gridWorld.getState()); cout << endl;
        gridWorld.display();
        turns++;
    }
    cout << "Agent accumulated reward: " << myAgent.getReward() << endl;
    cout << "Agent played with policy: " << endl;
    displayPolicyGrid(myAgent.getPolicy());
}

void processTurn(int &turnCounter, string userInput, Agent &agent, GridWorld &gridWorld) {
    turnCounter++;
    userInput = "_";
    gridWorld.display();
    gridWorld.displayRewardMap();
    agent.collectReward();
    agent.getStateEstimate();
    cout << "=================" << endl;
}

