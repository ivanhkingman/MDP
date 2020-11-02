#include "valueiteration.hpp"

ValueIteration::ValueIteration() {

}

ValueIteration::ValueIteration(MDP mdp, float gamma, float threshold) 
: m_mdp(mdp), m_gamma(gamma), m_threshold(threshold) 
{

}

ValueIteration::~ValueIteration() {
    
}

bool ValueIteration::verifyOwnerMatch(Agent owner) {
    return (m_mdp.getSize() == owner.getMdp().getSize());
}

void ValueIteration::run() {
    cout << "Running algorithm: value iteration" << endl;
    stateSpace S = m_mdp.getStateSpace();
    transitionMap T = m_mdp.getTransitionMap();
    actionSpace A = m_mdp.getActionSpace();
    rewardMap R = m_mdp.getRewardMap();
    valueMap V = zeroInitializeValueMap(S);
    double delta = DBL_MAX;
    int numberOfIterations = 0;
    while ( delta > (m_threshold*(1-m_gamma)/m_gamma) ) {
        valueMap VPrev = V;
        delta = 0;
        for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
            state state = *stateIt;
            V.at(state) = greatestExpectedValueSum(state, A, T, S, R, V, m_gamma);
            
            if ( abs(V.at(state) - VPrev.at(state)) > delta) {
                delta = abs(V.at(state)) - VPrev.at(state);
            }
        }
        numberOfIterations++;
    }
    cout << "Terminated after: " <<  numberOfIterations << " iterations" << endl;
    if (m_hasOwner) {
        m_owner->setValueMap(V);
    }
    m_V = V;
    derivePolicyFromValueMap();
    m_hasRun = true;
}

void ValueIteration::derivePolicyFromValueMap() {
    /*if (!m_hasRun) {
        cout << "Unable to derive policy, algorithm has not been run." << endl; 
        return;
    }*/
    policy Pi;
    stateSpace S = m_mdp.getStateSpace();
    actionSpace A = m_mdp.getActionSpace();
    transitionMap T = m_mdp.getTransitionMap();
    rewardMap R = m_mdp.getRewardMap();
    for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
        state fromState = *fromStateIt;
        action bestAction = argMaxExpectedValue(A, S, fromState, T, R, m_V, m_gamma);
        Pi[fromState] = bestAction;  
    }
    if (m_hasOwner) {
        m_owner->setPolicy(Pi);
    }
    
}


void printValueMap(valueMap V) {
    for (auto mapIterator = V.begin(); mapIterator != V.end(); mapIterator++) {
        cout << "State: [" << mapIterator->first[0] << ", " << mapIterator->first[1] << "] has value " << mapIterator->second << endl;
    }
}