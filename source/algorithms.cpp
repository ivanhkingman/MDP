#include "algorithms.hpp"

valueMap valueIteration(MDP mdp, const double threshold, double gamma) {
    stateSpace S = mdp.getStateSpace();
    transitionMap T = mdp.getTransitionMap();
    actionSpace A = mdp.getActionSpace();
    rewardMap R = mdp.getRewardMap();
    valueMap V = zeroInitializeValueMap(S);
    double delta = DBL_MAX;
    int numberOfIterations = 0;
    while ( delta > (threshold*(1-gamma)/gamma) ) {
        valueMap VPrev = V;
        delta = 0;
        for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
            state state = *stateIt;
            V.at(state) = R.at(state) + gamma * greatestExpectedValueSum(state, VPrev, A, T, S);
            if ( abs(V.at(state) - VPrev.at(state)) > delta) {
                delta = abs(V.at(state)) - VPrev.at(state);
            }
        }
        numberOfIterations++;
    }
    cout << "Terminated after: " <<  numberOfIterations << " iterations" << endl;
    return V;
}

valueMap zeroInitializeValueMap(stateSpace S) {
    valueMap V;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        V.insert(pair<state,double>(*stateIt, 0));
    }
    return V;
}

double greatestExpectedValueSum(state fromState, valueMap VPrev, actionSpace A, transitionMap T, stateSpace S) {
    double greatestExpectedValueSum = -DBL_MAX;
    for (auto actionIt = A.begin(); actionIt != A.end(); actionIt++) {
        action withAction = *actionIt;
        double expectedValueSum = 0;
        for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++) {
            state toState = *toStateIt;
            Transition transition(fromState, toState, withAction);
            double expectedValue = T.at(transition)*VPrev.at(toState);
            expectedValueSum += expectedValue;
        }
    if (expectedValueSum > greatestExpectedValueSum) {greatestExpectedValueSum = expectedValueSum;}
    }
    return greatestExpectedValueSum;
}

void printValueMap(valueMap V) {
    for (auto mapIterator = V.begin(); mapIterator != V.end(); mapIterator++) {
        cout << "State: [" << mapIterator->first[0] << ", " << mapIterator->first[1] << "] has value " << mapIterator->second << endl;
    }
}

policy derivePolicyFromValueMap(valueMap V, MDP mdp) {
    // 
}