#include "utils.hpp"

stateSpace create2DGridWorld(int size) {

    stateSpace gridWorld;
    state position;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y< size; y++) {
            position = {x,y};
            gridWorld.insert(position);
        }
    }
    
    return gridWorld;  
}

void printGridWolrd(int dim, state position) {
    for (int x = 0;  x < dim; x++ ) {
        for (int y = 0; y < dim; y++) {
            state tile {x,y};
            if (tile == position) {
                cout << "[x]";
            }
            else
                cout << "[ ]";
        }
        cout << endl;
    }
}

rewardMap generateRandomRewardMap(stateSpace gridWorld, int low, int high) {
    rewardMap rewardMap;
    for (auto it = gridWorld.begin(); it != gridWorld.end(); it++) {
        int randomReward = rand() % high + low;
        rewardMap.insert(pair<state, int>(*it, randomReward));
    }
    return rewardMap;
}

void printRewardMap(map<vector<int>, int> rewardMap, int dim) {
    for (int x = 0;  x < dim; x++ ) {
        for (int y = 0; y < dim; y++) {
            vector<int> tile {x,y};
            cout << "[" << rewardMap[tile] << "]";
        }
        cout << endl;
    }
}


//! Generates a default transition map where the probability of any transition is zero
transitionMap generateZeroTransitionMap(actionSpace A, stateSpace S) {
    transitionMap zeroTransitionMap;
    for (auto leavingState = S.begin(); leavingState != S.end(); leavingState++) {
        for (auto enteringState = S.begin(); enteringState != S.end(); enteringState++) {
            for (auto withAction = A.begin(); withAction != A.end(); withAction++) {
                Transition transition(*leavingState, *enteringState, *withAction);
                zeroTransitionMap.insert(pair<Transition, probability>(transition, 0));
            }
        }
    }
    return zeroTransitionMap;
}

//! The gridworld transition map is defined by the following rules:
//!     The agent has 80% chance of successfully going in the direction it chose
//!     The other 20% are equally divided between going left or right from the chosen direction
//!     If the agent tries to leave the grid world, it will remain in the same tile
transitionMap generateGridWorldTransitionMap(int dim, actionSpace A, stateSpace S) {
    transitionMap gridWorldTransitionMap = generateZeroTransitionMap(A, S);
    for (auto state = S.begin(); state != S.end(); state++) {
        if (isOnUpperEdge(*state, S, dim)) {
            
        }
        else {

        }
    }
    return gridWorldTransitionMap;
}



bool isOnUpperEdge(state state, stateSpace S, int dim) {
    return true;
}