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

void Transition::printLeavingState(){
    cout << "Leaving state: [";
    for (auto atribute = m_leavingState.begin(); atribute != m_leavingState.end(); atribute++) {
        cout << *atribute << ", ";
    }
    cout << "]";
}

void Transition::printEnteringState(){
    cout << "Entering state: [";
    for (auto atribute = m_enteringState.begin(); atribute != m_enteringState.end(); atribute++) {
        cout << *atribute << ", ";
    }
    cout << "]";
}

void Transition::printWithAction(){
    cout << "With action: " << m_withAction;
}

void Transition::print() {
    this->printLeavingState();
    this->printEnteringState();
    this->printWithAction();
}


bool operator < (const Transition &t1, const Transition &t2) {

    if (t1.m_leavingState < t2.m_leavingState) return true;
    if (t1.m_leavingState > t2.m_leavingState) return false;

    if (t1.m_enteringState < t2.m_enteringState) return true;
    if (t1.m_enteringState > t2.m_enteringState) return false;

    if (t1.m_withAction < t2.m_withAction) return true;
    if (t1.m_withAction > t2.m_withAction) return false;

    return false;
}

void printState(state st) {
    cout << "[";
    for (auto it = st.begin(); it != st.end(); it++) {
        cout << st[*it] << ",";
    } 
    cout << "]";
    
}