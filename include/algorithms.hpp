#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>


#include "mdp.hpp"
#include <float.h>


using namespace std;
using stateActionPair = pair<state, action>;
using policy = map<state, action>;                              // P : S    -> A
using valueMap = map<state, double>;                            // V : S    -> Real
using stateActionValueMap = map<stateActionPair, double>;       // Q : SxA  -> Real

//! Value iteration

valueMap valueIteration(MDP mdp, const double threshold, double gamma); // VAL-IT : mdp -> V
valueMap zeroInitializeValueMap(stateSpace S);

double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, double gamma);
double greatestExpectedValueSum(state fromState, actionSpace A, transitionMap T, stateSpace S, rewardMap R, valueMap V, double gamma);

policy derivePolicyFromValueMap(valueMap V, MDP mdp, double gamma);

void printValueMap(valueMap V);
void printPolicy(policy Pi);
void printStateActionValueMap(stateActionValueMap Q);

action argMaxExpectedValue(actionSpace A, stateSpace S, state fromState, transitionMap T, rewardMap R, valueMap V, double gamma);

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

