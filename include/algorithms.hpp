#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "mdp.hpp"

#include <float.h>


using namespace std;

using policy = map<state, action>;
using valueMap = map<state, double>;

valueMap zeroInitializeValueMap(stateSpace S);

double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, double gamma);

valueMap valueIteration(MDP mdp, const double threshold, double gamma);
double greatestExpectedValueSum(state fromState, actionSpace A, transitionMap T, stateSpace S, rewardMap R, valueMap V, double gamma);

policy derivePolicyFromValueMap(valueMap V, MDP mdp, double gamma);

void printValueMap(valueMap V);
void printPolicy(policy Pi);


