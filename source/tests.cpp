#include <iostream>

#include "tests.hpp"

void letUserPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double successRate) {
    myAgent.displayPosition();
    displayRewardMap(myMDP.getRewardMap(), dim);
    int playerTurns = 0;
    while(playerTurns < moves) {
        string userInput;
        cin >> userInput;
        if (userInput == "w") {
            playerTurns++;
            userInput = "_";
            myAgent.attemptMove(UP, successRate, dim);
            myAgent.displayPosition();
            displayRewardMap(myMDP.getRewardMap(), dim);
            myAgent.collectReward();
        }
        if (userInput == "s") {
            playerTurns++;
            userInput = "_";
            myAgent.attemptMove(DOWN, successRate, dim);
            myAgent.displayPosition();
            displayRewardMap(myMDP.getRewardMap(), dim);
            myAgent.collectReward();
        }
        if (userInput == "a") {
            playerTurns++;
            userInput = "_";
            myAgent.attemptMove(LEFT, successRate, dim);
            myAgent.displayPosition();
            displayRewardMap(myMDP.getRewardMap(), dim);
            myAgent.collectReward();
        }
        if (userInput == "d") {
            playerTurns++;
            userInput = "_";
            myAgent.attemptMove(RIGHT, successRate, dim);
            myAgent.displayPosition();
            displayRewardMap(myMDP.getRewardMap(), dim);
            myAgent.collectReward();
        }
        if (userInput == "e") {
            break;
        }
    }
    double agentReward = myAgent.getReward();
    cout << "You accumulated reward: " << myAgent.getReward() << endl;
}

void letAlgorithmPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double gamma, double successRate) {
    valueMap agentValueMap = valueIteration(myMDP, 0.01, gamma);
    policy agentPolicy = derivePolicyFromValueMap(agentValueMap, myMDP, gamma);

    for (int turn = 0; turn < moves; turn++) {
        action nextMove = agentPolicy.at(myAgent.getPosition());
        myAgent.attemptMove(nextMove, successRate, dim);
        myAgent.collectReward();
    }

    double agentReward = myAgent.getReward();
    cout << "Agent accumulated reward: " << myAgent.getReward() << endl;
    cout << "Agent used policy: " << endl;
    displayPolicy(agentPolicy, dim);
    myAgent.reset();

}