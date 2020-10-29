#include "gridworld.hpp"

GridWorld::GridWorld() {
    m_A = {UP, DOWN, LEFT, RIGHT};
    m_state = {0, 0};
}

GridWorld::GridWorld(const unsigned int DIMENSION, int minReward, int maxReward, probability successRate) 
: m_dimension(DIMENSION), m_moveSuccessRate(successRate)
{
    m_A = {UP, DOWN, LEFT, RIGHT};
    stateSpace grid;
    for (int x = 0; x < m_dimension; x++) {
        for (int y = 0; y< m_dimension; y++) {
            state tile = {x,y};
            grid.insert(tile);
        }
    }
    m_S = grid;
    m_state = {0, 0};
    void generateRandomRewardMap(int minReward, int maxReward);
    void generateGridWorldTransitionMap();

}

void GridWorld::reactToAction(action move) {
    float p = m_moveSuccessRate;
    float not_p = 1-p;
    float diceRoll = static_cast <float> (rand())/ static_cast <float> (RAND_MAX);
    if (p > diceRoll) {
        cout << "Move succeeded" << endl;
        executeMove(move);
        return;
    }
    if ((p + (not_p)/2) > diceRoll) {
        cout << "Move failed, flipping clockwize" << endl;
        move = flipClockwize(move);
        executeMove(move);
        return;
    } else {
        cout << "Move failed, flipping counter-clockwize" << endl;
        move = flipCounterClockwize(move);
        executeMove(move);
        return;
    }
}

void GridWorld::executeMove(action move) {
    if ((isOnUpperEdge(m_state)) && move== UP) {
        cout << "Tried to move up out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnLowerEdge(m_state)) && move == DOWN) {
        cout << "Tried to move down out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnLeftEdge(m_state)) && move == LEFT) {
        cout << "Tried to move left out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnRightEdge(m_state)) && move == RIGHT) {
        cout << "Tried to move right out of the map. Stayed in place" << endl;
        return;
    }

    switch(move) {
        case UP:
            cout << "Moving up" << endl;
            m_state = getTileAbove(m_state);
            break;
        case DOWN:
            cout << "Moving down" << endl;
            m_state = getTileBelow(m_state);
            break;
        case LEFT:
            cout << "Moving left" << endl;
            m_state = getTileToLeft(m_state);
            break;
        case RIGHT:
            cout << "Moving right" << endl;
            m_state = getTileToRight(m_state);
            break;
    }
}


//! The gridworld transition map is defined by the following rules:
//!     The agent has fixed chance of successfully going in the direction it chose
//!     If the agent is unsuccessfull, it will either go left or right of what it tried
//!     If the agent tries to leave the grid world, it will remain in the same tile
void GridWorld::generateGridWorldTransitionMap() {
    transitionMap gridWorldTransitionMap;
    probability success = m_moveSuccessRate;
    probability fail = 1 - success;
    for (auto leavingStateIt = m_S.begin(); leavingStateIt != m_S.end(); leavingStateIt++) {
        
        state leavingState = *leavingStateIt;
        state tileAbove = getTileAbove(leavingState);
        state tileBelow = getTileBelow(leavingState);
        state tileToRight = getTileToRight(leavingState);
        state tileToLeft = getTileToLeft(leavingState);

        if (isOnUpperEdge(leavingState)) {
            tileAbove = leavingState; // So that agent cannot leave grid world
        }
        if (isOnLowerEdge(leavingState)) {
            tileBelow = leavingState; // ="=
        }
        if (isOnRightEdge(leavingState)) {
            tileToRight = leavingState; // ="=
        }
        if (isOnLeftEdge(leavingState)) {
            tileToLeft = leavingState; // ="=
        }
        

        // Insert all possible outcomes when trying to go down
        Transition goingBelowWithDown(leavingState, tileBelow, DOWN);
        Transition goingLeftWithDown(leavingState, tileToLeft, DOWN);
        Transition goingRightWithDown(leavingState, tileToRight, DOWN);

        gridWorldTransitionMap.insert(pair<Transition, probability>(goingBelowWithDown, success));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithDown, fail/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithDown, fail/2));

        // Insert all possible outcomes when trying to go up
        Transition goingAboveWithUp(leavingState, tileAbove, UP);
        Transition goingLeftWithUp(leavingState, tileToLeft, UP);
        Transition goingRightWithUp(leavingState, tileToRight, UP);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingAboveWithUp, success));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithUp, fail/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithUp, fail/2));

        // Insert all possible outcomes when trying to go left
        Transition goingLeftWithLeft(leavingState, tileToLeft, LEFT);
        Transition goingUpWithLeft(leavingState, tileAbove, LEFT);
        Transition goingDownWithLeft(leavingState, tileToRight, LEFT);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingLeftWithLeft, success));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingUpWithLeft, fail/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingDownWithLeft, fail/2));

        // Insert all possible outcomes when trying to go right
        Transition goingRightWithRight(leavingState, tileToRight, RIGHT);
        Transition goingUpWithRight(leavingState, tileAbove, RIGHT);
        Transition goingDownWithRight(leavingState, tileBelow, RIGHT);
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingRightWithRight, success));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingUpWithRight, fail/2));
        gridWorldTransitionMap.insert(pair<Transition, probability>(goingDownWithRight, fail/2));

    }

    fillIncompleteTransitionMap(gridWorldTransitionMap, m_A, m_S);
    m_T = gridWorldTransitionMap;

}

//! Maps unspecified transitions to zero
//! Todo: Consider adding lambda function argument to decide how unspecified probabilities should be mapped
void fillIncompleteTransitionMap(transitionMap &T, actionSpace A, stateSpace S) {
    int count = 0;
    for (auto leavingState = S.begin(); leavingState != S.end(); leavingState++) {
        for (auto enteringState = S.begin(); enteringState != S.end(); enteringState++) {
            for (auto withAction = A.begin(); withAction != A.end(); withAction++) {
                Transition transition(*leavingState, *enteringState, *withAction);
                T.insert(pair<Transition, probability>(transition, 0));
                count++;
            }
        }
    }
}



bool GridWorld::isOnUpperEdge(state state) {
    return (state[1] == m_dimension-1);
}

bool GridWorld::isOnLeftEdge(state state) {
    return (state[0] == 0);
}

bool GridWorld::isOnLowerEdge(state state) {
    return (state[1] == 0);
}

bool GridWorld::isOnRightEdge(state state) {
    return (state[0] == m_dimension-1);
}

bool GridWorld::isOnAnyEdge(state state) {
    return (isOnRightEdge(state) || isOnLowerEdge(state) || isOnLeftEdge(state) || isOnUpperEdge(state));
}

state GridWorld::getTileBelow(state fromState) {
    state tileBelow = {fromState[0], fromState[1] -1};
    return tileBelow;
}

state GridWorld::getTileAbove(state fromState) {
    state tileAbove = {fromState[0], fromState[1] + 1};
    return tileAbove;
}

state GridWorld::getTileToLeft(state fromState) {
    state tileToLeft = {fromState[0] - 1, fromState[1]};
    return tileToLeft;
}

state GridWorld::getTileToRight(state fromState) {
    state tileToRight = {fromState[0] + 1, fromState[1]};
    return tileToRight;
}

action GridWorld::flipCounterClockwize(action moveDirection) {
    switch (moveDirection) {
        case UP:
            moveDirection = LEFT;
            break;
        case DOWN:
            moveDirection = RIGHT;
            break;
        case LEFT:
            moveDirection = DOWN;
            break;
        case RIGHT:
            moveDirection = UP;
            break;
        default:
            cout << "Something went wrong!" << endl;
            break;
    }
    return moveDirection;
}

action GridWorld::flipClockwize(action moveDirection) {
    switch(moveDirection) {
        case UP:
            moveDirection = RIGHT;
            break;
        case DOWN:
            moveDirection = LEFT;
            break;
        case LEFT:
            moveDirection = UP;
            break;
        case RIGHT:
            moveDirection = DOWN;
            break;
        default:
            cout << "Something went wrong!" << endl;
            break;
    }
    return moveDirection;
}

void GridWorld::displayGridWorld() {
    for (int y = m_dimension-1;  y >= 0; y-- ) {
        for (int x = 0; x < m_dimension; x++) {
            state tile {x,y};
            if (tile == m_state) {
                cout << "[x]";
            }
            else
                cout << "[ ]";
        }
        cout << endl;
    }
}



void GridWorld::displayRewardMap() {
    for (int y = m_dimension-1;  y >= 0; y-- ) {
        for (int x = 0; x < m_dimension; x++) {
            state tile {x,y};
            cout << "[" << m_R[tile] << "]";
        }
        cout << endl;
    }
}

void displayPolicyGrid(valueMap V) {
    if (!isSquareSet(V)) {
        cout << "Policy map must be square grid" << endl;
        return;
    }
    else {
        int dimension = sqrt(V.size());
        for (int y = dimension-1;  y >= 0; y-- ) {
            for (int x = 0; x < dimension; x++) {
                state tile {x,y};
                cout << "[" << V[tile] << "]";
            }
            cout << endl;
        }
    }
}

void displayPolicyGrid(policy Pi) {
    if (!isSquareSet(Pi)) {
        cout << "Policy map must be square grid" << endl;
    }
    else {
        int dimension = sqrt(Pi.size());
        for (int y = dimension-1;  y >= 0; y-- ) {
            for (int x = 0; x < dimension; x++) {
                state tile {x,y};
                switch (Pi.at(tile)) {
                    case UP:
                        cout << "[^]"; break;
                    case DOWN:
                        cout << "[v]"; break;
                    case RIGHT:
                        cout << "[>]"; break;
                    case LEFT:
                        cout << "[<]"; break;
                }
            }
            cout << endl;
        }
    }
}

template <typename T>
bool isSquareSet(T set) {
    float root = sqrt(set.size());
    float floor = round(root);
    return ((root - floor) == 0);
}
