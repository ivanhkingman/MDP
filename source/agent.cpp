#include "agent.hpp"
#include "utils.hpp"

#include <random> 

Agent::Agent() {

}

Agent::~Agent() {

}

void Agent::attemptMove(action moveDirection) {
    int diceThrow = rand() %  1 + 10;
    if (diceThrow <= 8) {
        this->executeMove(moveDirection);
    }
    if (diceThrow == 9) {
        moveDirection = flipClockWize(moveDirection);
        this->executeMove(moveDirection);
    }
    if (diceThrow == 10) {
        moveDirection = flipCounterClockwize(moveDirection);
        this->executeMove(moveDirection);
    }
}

void Agent::executeMove(action moveDirection) {
    if ((isOnUpperEdge(this->m_state, 4)) || moveDirection == UP) {
        this->m_state; //remains in place
    }
    if ((isOnLowerEdge(this->m_state)) || moveDirection == DOWN) {
        //remains in place
    }
    if 

}



