#include "algorithm.hpp"

Algorithm::Algorithm() {

}

Algorithm::~Algorithm() {
    
}

void Algorithm::run() {};

void Algorithm::setOwner(Agent &owner) {
    if (m_hasOwner) {
        cout << "Algorithm already has owner" << endl;
        return;
    }
    if (!this->verifyOwnerMatch(owner)) {
        cout << "Agent and algorithm have conflicting world views" << endl;
        return;
    }
    cout << "Algorithm owner was set." << endl;
    m_hasOwner = true;
    m_owner = &owner;
}

void Algorithm::detatchOwner() {
    m_owner = NULL;
    delete m_owner;
}

bool Algorithm::verifyOwnerMatch(Agent owner) { return false; };

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

// Todo: Dont extract the members of MDP before passing them to argMaxExpectedValue, just send the whole MDP
action argMaxExpectedValue(actionSpace A, stateSpace S, state fromState, transitionMap T, rewardMap R, valueMap V, double gamma) {
    double greatestExpectedValue = -DBL_MAX;
    action bestAction;
    for (auto withActionIt = A.begin(); withActionIt != A.end(); withActionIt++) {
            action withAction = *withActionIt;
            double expectedValueSum = 0;
            for (auto toStateIt = S.begin(); toStateIt != S.end(); toStateIt++) {
                state toState = *toStateIt;
                Transition transition(fromState, toState, withAction);
                double expectedValue = T.at(transition)*(R.at(toState) + gamma*V.at(toState));
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


policy zeroInitializePolicy(const stateSpace S) {
    policy Pi;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        Pi.insert(pair<state, action>(*stateIt, 0));
    }
    return Pi;
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
                // need to work on agent class to make algorithm a member variable of agent
                // need to make environment a class...

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

valueMap zeroInitializeValueMap(stateSpace S) {
    valueMap V;
    for (auto stateIt = S.begin(); stateIt != S.end(); stateIt++) {
        V.insert(pair<state,double>(*stateIt, 0));
    }
    return V;
}