#include <iostream>
#include "utils.hpp"
#include "mdp.hpp"

using namespace std;

int main(){

    stateSpace myGridWorld = create2DGridWorld(4);
    rewardMap myRewardMap = generateRandomRewardMap(myGridWorld, -5, 10);

    MDP myMDP;

    myMDP.setStateSpace(myGridWorld);
    myMDP.setRewardMap(myRewardMap);

    myMDP.printRewardMap();
    
    return 0;
}