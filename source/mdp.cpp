#include "mdp.hpp"

MDP::MDP(){

}

MDP::MDP(stateSpace S, transitionMap T, actionSpace A, rewardMap R) : m_S(S), m_T(T), m_A(A), m_R(R)
{

}

MDP::~MDP(){

}

void MDP::setStateSpace(stateSpace S) { m_S = S;}

void MDP::setTransitionMap(transitionMap T) { m_T = T; }

void MDP::setActionSpace(actionSpace A) { m_A = A; }

void MDP::setRewardMap(rewardMap R) {m_R = R; }

void MDP::printStateSpace() {
    for (auto state = m_S.begin(); state != m_S.end(); state++) {
        for (auto attribute = state->begin(); attribute != state->end(); attribute++){
            cout << *attribute << " ";
        }
        cout << endl;
    }
}
void MDP::printTransitionMap() {
    for (auto transitionProb = m_T.begin(); transitionProb != m_T.end(); transitionProb++) {
        Transition transition = transitionProb->first;
        probability prob = transitionProb->second;
        transition.print(); 
        cout << " has probability of: " << prob << endl;
    }
}

void MDP::printActionSpace() {
    for (auto action = m_A.begin(); action != m_A.end(); action++) {
        cout << *action << ", ";
    }
}

void MDP::printRewardMap() {
    for (auto state = m_R.begin(); state != m_R.end(); state++) {
        cout << "Reward of state [";
        for (auto attribute = state->first.begin(); attribute != state->first.end(); attribute++) {
            cout << *attribute << " ";
        }
        cout << "] is " << state->second << endl;
    }
};

void MDP::print() {
    this->printStateSpace();
    this->printTransitionMap();
    this->printActionSpace();
    this->printRewardMap();
}

stateSpace getStateSpace();
transitionMap getTransitionMap();
actionSpace getActionSpace();
rewardMap getRewardMap();

