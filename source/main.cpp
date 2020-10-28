#include <iostream>
#include <unistd.h>


#include "agent.hpp"
#include "algorithms.hpp"

using namespace std;

int main(){

    // Set parameters of gridWorld
    int dim = 5;
    double successRate = 0.8;
    int moves = 100;

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

    cout << "Agents played on map: " << endl;
    displayRewardMap(myRewardMap, dim);

    // Create an agent
    Agent myAgent;
    myAgent.setMDP(myMDP);
    policy myPolicy;
    valueMap myValueMap;

    double agentReward = 0;

    // Gamma 0.2 (greedy)
    myValueMap = valueIteration(myMDP, 0.01, 0.2);
    myPolicy = derivePolicyFromValueMap(myValueMap, myMDP, 0.2);

    for (int turn = 0; turn < moves; turn++) {
        action nextMove = myPolicy.at(myAgent.getPosition());
        myAgent.attemptMove(nextMove, successRate, dim);
        // myAgent.displayPosition();
        myAgent.collectReward();
        // usleep(1);
    }

    agentReward = myAgent.getReward();
    cout << "Greedy agent accumulated reward: " << myAgent.getReward() << endl;
    cout << "Greedy agent used policy: " << endl;
    displayPolicy(myPolicy, dim);
    myAgent.reset();

    // Gamma 0.5 (medium)
    myValueMap = valueIteration(myMDP, 0.01, 0.5);
    myPolicy = derivePolicyFromValueMap(myValueMap, myMDP, 0.5);

    for (int turn = 0; turn < moves; turn++) {
        action nextMove = myPolicy.at(myAgent.getPosition());
        myAgent.attemptMove(nextMove, successRate, dim);
        // myAgent.displayPosition();
        myAgent.collectReward();
        // usleep(1);
    }

    agentReward = myAgent.getReward();
    cout << "Medium greedy agent accumulated reward: " << myAgent.getReward() << endl;
    cout << "Medium greedy agent used policy: " << endl;
    displayPolicy(myPolicy, dim);
    myAgent.reset();

    // Gamma 0.8 (non-greedy)
    myValueMap = valueIteration(myMDP, 0.01, 0.8);
    myPolicy = derivePolicyFromValueMap(myValueMap, myMDP, 0.8);

    for (int turn = 0; turn < moves; turn++) {
        action nextMove = myPolicy.at(myAgent.getPosition());
        myAgent.attemptMove(nextMove, successRate, dim);
        // myAgent.displayPosition();
        myAgent.collectReward();
        // usleep(1);
    }

    agentReward = myAgent.getReward();
    cout << "Non-greedy agent accumulated reward: " << myAgent.getReward() << endl;
    cout << "Non-greedy agent used policy: " << endl;
    displayPolicy(myPolicy, dim);
    myAgent.reset();

    


    /*
    cout << "Value map: " << endl;
    displayValueMap(myValueMap, dim);
    cout << endl;
    cout << "Reward map: " << endl;
    displayRewardMap(myMDP.getRewardMap(), dim);
    cout << "Policy: " << endl;
    displayPolicy(myPolicy, dim);
    myAgent.displayPosition();
    */

    // Let agent play the game for 10 turns


    /*    
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
    
    cout << "Your score is: " << myAgent.getReward() << endl;
    cout << "The agents score was: " << agentReward << endl;
    cout << "Agent played with the following policy: " << endl;
    displayPolicy(myPolicy, dim);

    */

    return 0;
}