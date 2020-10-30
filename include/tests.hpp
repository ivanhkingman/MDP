#pragma once

#include "mdp.hpp"
#include "agent.hpp"
#include "gridworld.hpp"

void letUserPlayGridWorld(GridWorld gridWorld, int nTurns);
void letAgentPlayGridWorld(Agent myAgent, GridWorld gridWorld, int nTurns);
void processTurn(int &turnCounter, string userInput, Agent &agent, GridWorld &gridWorld);