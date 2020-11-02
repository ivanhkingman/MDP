#pragma once

#include <iostream>
#include <cstdlib>
#include <float.h>

#include "mdp.hpp"
#include "agent.hpp"

using namespace std;

class Algorithm {
    public:
        Algorithm();
        ~Algorithm();


        void setOwner(Agent &owner);
        void detatchOwner();
        virtual void run();
    
    protected:
        Agent* m_owner;
        bool m_hasRun = false;
        bool m_hasOwner = false;
        
        virtual bool verifyOwnerMatch(Agent owner);
    
};


// Methods commonly used by different aglorithms
double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, float gamma);
double greatestExpectedValueSum(state fromState, actionSpace A, transitionMap T, stateSpace S, rewardMap R, valueMap V, double gamma);
action argMaxExpectedValue(actionSpace A, stateSpace S, state fromState, transitionMap T, rewardMap R, valueMap V, double gamma);

// Print various sets
void printPolicy(policy Pi);
void printStateActionValueMap(stateActionValueMap Q);
void printValueMap(valueMap V);

// Zero initializations
valueMap zeroInitializeValueMap(stateSpace S);
policy zeroInitializePolicy(const stateSpace S);


//! Q-learning
stateActionValueMap Q_learning(stateSpace S, actionSpace A); 

stateActionValueMap zeroInitializeQ(stateSpace S, actionSpace A);

//! SARSA
stateActionValueMap sarsa();

