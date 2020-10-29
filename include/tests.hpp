#pragma once

#include "mdp.hpp"
#include "agent.hpp"
#include "gridworld.hpp"

void letUserPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double successRate);
void letAlgorithmPlayGridWorld(Agent myAgent, MDP myMDP, int dim, int moves, double gamma, double successRate);
void processTurn(int &turnCounter, string userInput, Agent agent, GridWorld gridWorld);