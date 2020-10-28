#include "agent.hpp"


Agent::Agent() {
    srand((unsigned int)time(NULL));
    m_state = {0, 0};
}

Agent::~Agent() {
    m_state = {0, 0};
}

void Agent::setMDP (MDP mdp) {
    srand((unsigned int)time(NULL));
    m_mdp = mdp;
}

void Agent::attemptMove(action moveDirection, double SUCCESS, int dim) {
    int diceThrow = rand() %  10 + 1;
    int successThreshold = SUCCESS*10;
    int failThreshold = 10 - successThreshold;
    // cout << "Dice throw: " << diceThrow << endl;
    if (diceThrow <= successThreshold) {
        this->executeMove(moveDirection, dim);
        return;
    }
    if ((diceThrow > successThreshold) && (diceThrow <= successThreshold - failThreshold/2)){
        // cout << "Move failed" << endl;
        moveDirection = flipClockwize(moveDirection);
        this->executeMove(moveDirection, dim);
        return;
    }
    else {
        // cout << "Move failed" << endl;
        moveDirection = flipCounterClockwize(moveDirection);
        this->executeMove(moveDirection, dim);
        return;
    }
}

void Agent::executeMove(action moveDirection, int dim) {
    if ((isOnUpperEdge(m_state, dim)) && moveDirection == UP) {
        // cout << "Tried to move up out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnLowerEdge(m_state)) && moveDirection == DOWN) {
        // cout << "Tried to move down out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnLeftEdge(m_state)) && moveDirection == LEFT) {
        // cout << "Tried to move left out of the map. Stayed in place" << endl;
        return;
    }
    if ((isOnRightEdge(m_state, dim)) && moveDirection == RIGHT) {
        // cout << "Tried to move right out of the map. Stayed in place" << endl;
        return;
    }

    switch(moveDirection) {
        case UP:
            // cout << "Moving up" << endl;
            m_state = getTileAbove(m_state);
            break;
        case DOWN:
            // cout << "Moving down" << endl;
            m_state = getTileBelow(m_state);
            break;
        case LEFT:
            // cout << "Moving left" << endl;
            m_state = getTileToLeft(m_state);
            break;
        case RIGHT:
            // cout << "Moving right" << endl;
            m_state = getTileToRight(m_state);
            break;
    }
}

void Agent::collectReward() {
    rewardMap R = m_mdp.getRewardMap();
    int reward = R.at(m_state);
    m_totalReward += reward;
}

void Agent::displayPosition() {
    int dim = sqrt(m_mdp.getSize());
    displayGridWorld(dim, m_state);
    cout << "Agent position: [" << m_state[0] << ", " << m_state[1] << endl; 
}

state Agent::getPosition() {
    return m_state;
}

double Agent::getReward(){
    return m_totalReward;
}

void Agent::reset() {
    m_totalReward = 0;
    m_state = {0, 0};
}
