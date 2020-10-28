#pragma once
#include "mdp.hpp"
#include "agent.hpp"
#include "utils.hpp"

void letUserPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double successRate);
void letAlgorithmPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double gamma, double successRate);