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
//!     The other 20% are equally divided between going left or right leaving the chosen direction
//!     If the agent tries to leave the grid world, it will remain in the same tile
transitionMap generateGridWorldTransitionMap(int dim, actionSpace A, stateSpace S) {
    cout << "Debug: generateGridWorldTransitionMap was called" << endl;
    // transitionMap gridWorldTransitionMap = generateZeroTransitionMap(A, S);

    transitionMap gridWorldTransitionMap;

    const probability SUCCESS = 0.8;
    const probability FAIL = 0.2;
    // enum actions {UP, DOWN, LEFT, RIGHT};

    for (auto leavingStateIt = S.begin(); leavingStateIt != S.end(); leavingStateIt++) {
        
        state leavingState = *leavingStateIt;
        
        state tileAbove = getTileAbove(leavingState);
        state tileBelow = getTileBelow(leavingState);
        state tileToRight = getTileToRight(leavingState);
        state tileToLeft = getTileToLeft(leavingState);

        if (isOnUpperEdge(leavingState, dim)) {
            cout << "State: [" << leavingState[0] << ", " << leavingState[1] << "] is on upper edge." << endl;
            tileAbove = leavingState; // So that agent cannot leave grid world
        }
        if (isOnLowerEdge(leavingState)) {
            cout << "State: [" << leavingState[0] << ", " << leavingState[1] << "] is on lower edge."<< endl;
            tileBelow = leavingState; // ="=
        }
        if (isOnRightEdge(leavingState, dim)) {
            cout << "State: [" << leavingState[0] << ", " << leavingState[1] << "] is on right edge."<< endl;
            tileToRight = leavingState; // ="=
        }
        if (isOnLeftEdge(leavingState)) {
            cout << "State: [" << leavingState[0] << ", " << leavingState[1] << "] is on left edge."<< endl;
            tileToLeft = leavingState; // ="=
        }
        

        // Insert all possible outcomes when trying to go down
        Transition goingBelowWithDown(leavingState, tileBelow, DOWN);
        Transition goingLeftWithDown(leavingState, tileToLeft, DOWN);
        Transition goingRightWithDown(leavingState, tileToRight, DOWN);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingBelowWithDown, SUCCESS));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithDown, FAIL/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithDown, FAIL/2));

        // Insert all possible outcomes when trying to go up
        Transition goingAboveWithUp(leavingState, tileAbove, UP);
        cout << "Going above with up: "; goingAboveWithUp.print(); cout << endl;
        Transition goingLeftWithUp(leavingState, tileToLeft, UP);
        Transition goingRightWithUp(leavingState, tileToRight, UP);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingAboveWithUp, SUCCESS));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithUp, FAIL/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithUp, FAIL/2));

        // Insert all possible outcomes when trying to go left
        Transition goingLeftWithLeft(leavingState, tileToLeft, LEFT);
        Transition goingUpWithLeft(leavingState, tileAbove, LEFT);
        Transition goingDownWithLeft(leavingState, tileToRight, LEFT);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithLeft, SUCCESS));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingUpWithLeft, FAIL/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingDownWithLeft, FAIL/2));

        // Insert all possible outcomes when trying to go right
        Transition goingRightWithRight(leavingState, tileToRight, RIGHT);
        Transition goingUpWithRight(leavingState, tileAbove, RIGHT);
        Transition goingDownWithRight(leavingState, tileBelow, RIGHT);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithRight, SUCCESS));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingUpWithRight, FAIL/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingDownWithRight, FAIL/2));

    }

    fillIncompleteTransitionMap(gridWorldTransitionMap, A, S);
    return gridWorldTransitionMap;

}

//! Maps unspecified transitions to zero
//! Todo: Consider adding lambda function argument to decide how unspecified probabilities should be mapped
void fillIncompleteTransitionMap(transitionMap &T, actionSpace A, stateSpace S) {
    for (auto leavingState = S.begin(); leavingState != S.end(); leavingState++) {
        for (auto enteringState = S.begin(); enteringState != S.end(); enteringState++) {
            for (auto withAction = A.begin(); withAction != A.end(); withAction++) {
                Transition transition(*leavingState, *enteringState, *withAction);
                T.insert(pair<Transition, probability>(transition, 0));
            }
        }
    }
}


bool isOnUpperEdge(state state, int dim) {
    return (state[1] == dim-1);
}

bool isOnLeftEdge(state state) {
    return (state[0] == 0);
}

bool isOnLowerEdge(state state) {
    return (state[1] == 0);
}

bool isOnRightEdge(state state, int dim) {
    return (state[0] == dim-1);
}

state getTileBelow(state fromState) {
    state tileBelow = {fromState[0], fromState[1] -1};
    return tileBelow;
}

state getTileAbove(state fromState) {
    state tileAbove = {fromState[0], fromState[1] + 1};
    return tileAbove;
}

state getTileToLeft(state fromState) {
    state tileToLeft = {fromState[0] - 1, fromState[1]};
    return tileToLeft;
}

state getTileToRight(state fromState) {
    state tileToRight = {fromState[0] + 1, fromState[1]};
    return tileToRight;
}