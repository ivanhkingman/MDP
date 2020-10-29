#include "valueiteration.hpp"

ValueIteration::ValueIteration() {

}

ValueIteration::~ValueIteration() {

}

void ValueIteration::run() {
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
}

valueMap zeroInitializeValueMap(stateSpace S) {
    valueMap V;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        V.insert(pair<state,double>(*stateIt, 0));
    }
    return V;
}

void printValueMap(valueMap V) {
    for (auto mapIterator = V.begin(); mapIterator != V.end(); mapIterator++) {
        cout << "State: [" << mapIterator->first[0] << ", " << mapIterator->first[1] << "] has value " << mapIterator->second << endl;
    }
}