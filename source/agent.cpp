#include "agent.hpp"


Agent::Agent() {
    srand((unsigned int)time(NULL));
    m_stateEstimate = {0, 0};
}

Agent::~Agent() {
    m_stateEstimate = {0, 0};
}

void Agent::setMDP (MDP mdp) {
    srand((unsigned int)time(NULL));
    m_mdp = mdp;
}

void Agent::executeAction(action action) {
    m_environment.reactToAction(action);
}

void Agent::collectReward() {
    double collectedReward = m_environment.giveReward();
    m_totalReward += collectedReward;
}

void Agent::observeState() {
    m_stateEstimate = m_environment.getState();
}

void Agent::printStateEstimate() {
    
}

void Agent::deployInEnvironment(Environment environment) {
    m_environment = environment;
}

void Agent::attatchAlgorithm(Algorithm &algorithm) {
    m_algorithm = algorithm;
}

state Agent::getStateEstimate() {
    return m_stateEstimate;
}

double Agent::getReward(){
    return m_totalReward;
}

void Agent::reset() {
    m_totalReward = 0;
}

policy Agent::getPolicy() {
    return m_Pi;
}

void invokeAlgorithm() {
    m_algorithm.run();
}
