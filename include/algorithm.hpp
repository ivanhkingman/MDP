#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "mdp.hpp"
#include "agent.hpp"
#include <float.h>

using namespace std;
using stateActionPair = pair<state, action>;
using policy = map<state, action>;                              // P : S    -> A
using valueMap = map<state, double>;                            // V : S    -> Real
using stateActionValueMap = map<stateActionPair, double>;       // Q : SxA  -> Real

class Algorithm {
    public:
        Algorithm();
        ~Algorithm();
    
    private:
        virtual void run();
        bool m_hasRun = false;
        bool m_hasOwner = false;
        Agent owner;

};


// Methods commonly used by different aglorithms
double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, double gamma);
double greatestExpectedValueSum(state fromState, actionSpace A, transitionMap T, stateSpace S, rewardMap R, valueMap V, double gamma);
action argMaxExpectedValue(actionSpace A, stateSpace S, state fromState, transitionMap T, rewardMap R, valueMap V, double gamma);

// Print various sets
void printPolicy(policy Pi);
void printStateActionValueMap(stateActionValueMap Q);
void printValueMap(valueMap V);



//---

//! Policy iteration
policy policyIteration(MDP mpd, double gamma, double threshold);
policy zeroInitializePolicy(const stateSpace S);
valueMap policyEvaluation(MDP mdp, policy Pi, double threshold, double gamma);

//! Q-learning
stateActionValueMap Q_learning(stateSpace S, actionSpace A); 

stateActionValueMap zeroInitializeQ(stateSpace S, actionSpace A);

//! SARSA
stateActionValueMap sarsa();

