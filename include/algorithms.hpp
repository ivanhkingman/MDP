#pragma once

#include <map>
#include <vector>
#include <iostream>

#include "mdp.hpp"

using namespace std;

using policy = map<state, action>;
using valueMap = map<state, double>;

valueMap zeroInitializeValueMap(stateSpace S);

double maximizeValueOverAction(valueMap V, MDP mdp, state fromState, action withAction, double gamma);

valueMap valueIteration(MDP mdp, const double threshold, double gamma);

void printValueMap(valueMap V);


