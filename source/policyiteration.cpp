#include "policyiteration.hpp"

PolicyIteration::PolicyIteration() {

}

PolicyIteration::PolicyIteration(MDP mdp, double gamma, double threshold)
: m_mdp(mdp), m_gamma(gamma), m_threshold(threshold) {

}

PolicyIteration::~PolicyIteration() {

}

void PolicyIteration::run() {
    cout << "Running policy iteration" << endl;
    stateSpace S = m_mdp.getStateSpace();
    actionSpace A = m_mdp.getActionSpace();
    rewardMap R = m_mdp.getRewardMap();
    transitionMap T = m_mdp.getTransitionMap();
    policy Pi = zeroInitializePolicy(S);
    policy PrevPi = zeroInitializePolicy(S);
    int iterations = 0;
    do {
        PrevPi = Pi;
        policyEvaluation(Pi);
        
        for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
            state fromState = *fromStateIt;
            action bestAction = argMaxExpectedValue(A, S, fromState, T, R, m_V, m_gamma);
            Pi.at(fromState) = bestAction;
        }
        iterations++;
    } while (Pi != PrevPi);
    cout << "Policy evaluation terminated after " << iterations << " iterations." << endl;
    if (m_hasOwner) {
        m_owner->setPolicy(Pi);
    }
    m_Pi = Pi;
}

void PolicyIteration::policyEvaluation(policy Pi) {
    stateSpace S = m_mdp.getStateSpace();
    actionSpace A = m_mdp.getActionSpace();
    transitionMap T = m_mdp.getTransitionMap();
    rewardMap R = m_mdp.getRewardMap();
    valueMap V = zeroInitializeValueMap(S);
    double delta = 0;
    int iterations = 0;
    do {
        delta = 0;
        for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
            state fromState = *fromStateIt;
            double v = V.at(fromState);
            action withAction = Pi.at(fromState);
            double expectedValueSum = 0;
            for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++) {
                state toState = *toStateIt;
                Transition transition(fromState, toState, withAction);
                double expectedValue = T.at(transition)*(R.at(fromState) + m_gamma*V.at(toState));
                expectedValueSum += expectedValue;
                // cout << "Expected value sum: " << expectedValueSum << endl;
            }
            V.at(fromState) = expectedValueSum;
            // cout << "Change in value: " << abs(v - V.at(fromState) > delta) << endl;
            if ((abs(v - V.at(fromState)) > delta)) {delta = abs(v - V.at(fromState)); }
            }
        iterations++; 
    } while (delta>m_threshold );
    if (m_hasOwner) {
        m_owner->setValueMap(V);
    }
    m_V = V;
}

bool PolicyIteration::verifyOwnerMatch(Agent agent) {
    // do nothing for now
    return true;
}