#include "algorithms.hpp"

valueMap zeroInitializeValueMap(stateSpace S) {
    valueMap V;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        V.insert(pair<state,double>(*stateIt, 0));
    }
    return V;
}

double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, double gamma) {
    double expectedValueSum;
    stateSpace S = mdp.getStateSpace();
    transitionMap T = mdp.getTransitionMap(); 
    rewardMap R = mdp.getRewardMap();
    for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++)
        {
            Transition transition(fromState, *toStateIt, withAction);
            double expectedValue = T.at(transition) * (R.at(*toStateIt) + gamma * V.at(*toStateIt));
            expectedValueSum += expectedValue;
        }
    return expectedValueSum;
}

valueMap valueIteration(MDP mdp, const double threshold, double gamma) {
    float delta = 0;
    stateSpace S = mdp.getStateSpace();
    actionSpace A = mdp.getActionSpace();
    transitionMap T = mdp.getTransitionMap();
    rewardMap R = mdp.getRewardMap();
    valueMap V = zeroInitializeValueMap(S);

    do {
        for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
            state fromState = *fromStateIt;
            valueMap oldV(V);
            float greatestValueSum;
            for (auto withActionIt = A.begin(); withActionIt != A.end(); withActionIt++) {
                action withAction = *withActionIt;
                float valueSum = maximizeValueOverAction(V, mdp, fromState, withAction, gamma);
                greatestValueSum = max(greatestValueSum, valueSum);
            }
            V.at(fromState) = greatestValueSum;
            float delta2 = (oldV.at(fromState)-V.at(fromState));
            delta = max(delta, delta2 );
        }
    } while (delta > threshold);
    return V;
}


void printValueMap(valueMap V) {
    for (auto mapIterator = V.begin(); mapIterator != V.end(); mapIterator++) {
        cout << "State: [" << mapIterator->first[0] << ", " << mapIterator->first[1] << "] has value " << mapIterator->second << endl;
    }
}