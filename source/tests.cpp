#include "tests.hpp"

#include <iostream>

void letUserPlayGridWorld(Agent agent, MDP myMDP, int moves, GridWorld gridWorld) {
    gridWorld.displayRewardMap();
    gridWorld.displayGridWorld();
    int turnCounter = 0;
    while(turnCounter < moves) {
        string userInput;
        cin >> userInput;
        if (userInput == "w") {
            agent.executeAction(UP);
        }
        if (userInput == "s") {
            agent.executeAction(DOWN);
        }
        if (userInput == "a") {
            agent.executeAction(LEFT);
        }
        if (userInput == "d") {
            turnCounter++;
            userInput = "_";
            agent.executeAction(RIGHT);
        }
        if (userInput == "e") {
            break;
        }
        processTurn(turnCounter, userInput, agent, gridWorld);
    }
    double agentReward = agent.getReward();
    cout << "You accumulated reward: " << agent.getReward() << endl;
}

void letAlgorithmPlayGridWorld(Agent agent, MDP myMDP, int moves, double gamma) {
    agent.runAlgorithm();
    for (int turn = 0; turn < moves; turn++) {
        action nextMove = agent.getPolicy().at(agent.getStateEstimate());
        agent.executeAction(nextMove);
        agent.collectReward();
    }

    double agentReward = agent.getReward();
    cout << "Value iteration algorithm accumulated reward: " << agent.getReward() << endl;
    cout << "Agent used policy: " << endl;
    displayPolicyGrid(agent.getPolicy());
    agent.reset();

}

void processTurn(int &turnCounter, string userInput, Agent agent, GridWorld gridWorld) {
    turnCounter++;
    userInput = "_";
    gridWorld.displayGridWorld();
    gridWorld.displayRewardMap();
    agent.collectReward();
}