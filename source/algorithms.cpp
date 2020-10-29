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
            V.at(state) = greatestExpectedValueSum(state, A, T, S, R, V, gamma);
            
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

double greatestExpectedValueSum(state fromState, actionSpace A, transitionMap T, stateSpace S, rewardMap R,valueMap V, double gamma) {
    double greatestExpectedValueSum = -DBL_MAX;
    // Todo: Make this into reusable method
    for (auto actionIt = A.begin(); actionIt != A.end(); actionIt++) {
        action withAction = *actionIt;
        double expectedValueSum = 0;
        for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++) {
            state toState = *toStateIt;
            Transition transition(fromState, toState, withAction);
            double expectedValue = T.at(transition)*(R.at(fromState) + gamma*V.at(toState));
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

// Todo: Dont extract the members of MDP before passing them to argMaxExpectedValue, just send the whole MDP
policy derivePolicyFromValueMap(valueMap V, MDP mdp, double gamma) {
    policy derivedPolicy;
    stateSpace S = mdp.getStateSpace();
    actionSpace A = mdp.getActionSpace();
    transitionMap T = mdp.getTransitionMap();
    rewardMap R = mdp.getRewardMap();
    for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
        state fromState = *fromStateIt;
        action bestAction = argMaxExpectedValue(A, S, fromState, T, R, V, gamma);
        derivedPolicy[fromState] = bestAction;  
    }
    return derivedPolicy;
}

// Todo: Dont extract the members of MDP before passing them to argMaxExpectedValue, just send the whole MDP
action argMaxExpectedValue(actionSpace A, stateSpace S, state fromState, transitionMap T, rewardMap R, valueMap V, double gamma) {
    double greatestExpectedValue = -DBL_MAX;
    action bestAction;
    for (auto withActionIt = A.begin(); withActionIt != A.end(); withActionIt++) {
            action withAction = *withActionIt;
            double expectedValueSum = 0; //
            for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++) {
                state toState = *toStateIt;
                Transition transition(fromState, toState, withAction);
                double expectedValue = T.at(transition)*(R.at(fromState) + gamma*V.at(toState));
                expectedValueSum = expectedValueSum + expectedValue;
            }
            if (expectedValueSum > greatestExpectedValue) {
                greatestExpectedValue = expectedValueSum; 
                bestAction = withAction; 
            }          
        }
    return bestAction;
}

void printPolicy(policy Pi) {
    for (auto mapIt = Pi.begin(); mapIt != Pi.end(); mapIt++) {
        state st = mapIt->first;
        action a = mapIt->second;
        cout << "Policy in state [" << st[0] << ", " << st[1] << "] is: " << a << endl;
    }
}

policy policyIteration(MDP mdp, double gamma, double threshold) {
    stateSpace S = mdp.getStateSpace();
    actionSpace A = mdp.getActionSpace();
    rewardMap R = mdp.getRewardMap();
    transitionMap T = mdp.getTransitionMap();
    policy Pi = zeroInitializePolicy(S);
    policy NextPi = Pi;
    int policyEvaluationIterations = 0;
    do {
        NextPi = Pi;
        valueMap V = policyEvaluation(mdp, Pi, threshold, gamma);
        
        for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
            state fromState = *fromStateIt;
            action bestAction = argMaxExpectedValue(A, S, fromState, T, R, V, gamma);
            Pi.at(fromState) = bestAction;
        }
        policyEvaluationIterations++;
    } while (NextPi != Pi);
    // cout << "Policy iteration iterations: " << policyEvaluationIterations << endl;
    return Pi;
}

policy zeroInitializePolicy(const stateSpace S) {
    policy Pi;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        Pi.insert(pair<state, action>(*stateIt, 0));
    }
    return Pi;
}

valueMap policyEvaluation(MDP mdp, policy Pi, double threshold, double gamma) {
    stateSpace S = mdp.getStateSpace();
    actionSpace A = mdp.getActionSpace();
    transitionMap T = mdp.getTransitionMap();
    rewardMap R = mdp.getRewardMap();
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
                double expectedValue = T.at(transition)*(R.at(fromState) + gamma*V.at(toState));
                expectedValueSum += expectedValue;
                // cout << "Expected value sum: " << expectedValueSum << endl;
            }
            V.at(fromState) = expectedValueSum;
            // cout << "Change in value: " << abs(v - V.at(fromState) > delta) << endl;
            if ((abs(v - V.at(fromState)) > delta)) {delta = abs(v - V.at(fromState)); }
            }
        iterations++; 
    } while (delta>threshold );
    // cout << "Policy evaluation Terminated after " << iterations << " iterations." << endl;
    return V;
}

stateActionValueMap Q_learning(stateSpace S, actionSpace A, state s0) {
    stateActionValueMap Q = zeroInitializeQ(S, A);
    int episodes;
    
    for (int e = 0; e < episodes; e++) {
        state s = s0;
        bool reachedGoalState = false;
        while (!reachedGoalState) {
            bool exploit = true;
            if (exploit) {
                double bestValue = -DBL_MAX;
                action bestAction;
                for (auto actionIt = A.begin(); actionIt != A.end(); actionIt++) {
                    action a = *actionIt;
                    stateActionPair stateAction(s0, a);
                    double value = Q.at(stateAction);
                    if (value > bestValue) {bestValue = value; bestAction = a;}
                }
            } else {
                // find another action
            }
            // perform action (either best or random)
                // how to perform action? pass message? invoke behavior in agent?
                // should agent be passed as parameter to function -- hmm
                // or return action, then run function again

            // observe new state, collect reward
                // I think algorithm and environment should be kept separate
                // Therefore, agent is the one who observes state, then informs algorithm

            // conclusion: This algorithm needs to communicate with the agent
                // need to work on agent class to make algorithm a member_variable of agent

        }
    }

    return Q;
}



stateActionValueMap zeroInitializeQ(stateSpace S, actionSpace A) {
    stateActionValueMap Q;
    for (auto fromStateIt = S.begin(); fromStateIt != S.end(); fromStateIt++) {
        state fromState = *fromStateIt;
        for (auto withActionIt = A.begin(); withActionIt != A.end(); withActionIt++) {
            action withAction = *withActionIt;
            stateActionPair stateAction(fromState, withAction);
            Q[stateAction] = 0;
        }
    }

    return Q;
}

void printStateActionValueMap(stateActionValueMap Q) {
    for (auto mapIt = Q.begin(); mapIt != Q.end(); mapIt++) {
        state state = mapIt->first.first;
        action action = mapIt->first.second; 
        cout << "State: " << "[ " << state[0] << ", " << state[1] << "],  action: " << action;
        cout << " has value: " << mapIt->second << endl;
    }
}

stateActionValueMap sarsa() {
    stateActionValueMap Q;

    return Q;
}

string stateToString(state state) {
    string stateAsString;

    return stateAsString;
}