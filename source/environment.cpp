#include "environment.hpp"

Environment::Environment() {

}

Environment::~Environment() {

}

void Environment::reactToAction(action action) {
    cout << "Environment reacting to action" << endl;
}

double Environment::giveReward() {
    return m_R.at(m_state);
}

state Environment::getState() {
    return m_state;
}

void Environment::generateRandomRewardMap(int from, int to) {
    // cout << "Random rewardmap being generated... " << endl;
    
    rewardMap R;
    for (auto it = m_S.begin(); it != m_S.end(); it++) {
        int reward = rand() % to + from;
        R.insert(pair<state, double>(*it, reward));
    }
    m_R = R;
}

void Environment::display() {
    cout << "Using base implementation of display" << endl;
}

//! Creates a perfect MDP model by copying the inner workings of the environment
MDP Environment::stealMdp(){
    MDP mdp(m_S, m_T, m_A, m_R);
    return mdp;
}
