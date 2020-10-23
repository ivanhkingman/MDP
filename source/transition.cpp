#include "transition.hpp"

Transition::Transition() {

}

Transition::Transition(state leavingState, state enteringState, action withAction) 
: m_leavingState(leavingState), m_enteringState(enteringState), m_withAction(withAction) {

}

Transition::~Transition() {
    
}

state Transition::getLeavingState() {
    return m_leavingState;
}

state Transition::getEnteringState() {
    return m_enteringState;
}

action Transition::getWithAction() {
    return m_withAction;
}

void Transition::setLeavingState(state leavingState) {
    m_leavingState = leavingState;
}

void Transition::setEnteringState(state enteringState) {
    m_enteringState = enteringState;
}

void Transition::setWithAction(action withAction) {
    m_withAction = withAction;
}