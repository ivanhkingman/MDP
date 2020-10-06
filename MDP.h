#ifndef MDP_H
#define MDP_H

#include <iostream>
#include "State.h"
#include "Transition.h"

#include <map>
#include <set>
#include <vector>

using namespace	std;
using probability = float;
using Action = int;

class MDP {
private:

	set<State> m_states;
	map<State, float> m_rewardMap;
	map<Transition, probability> m_stateTransitionMap;
	enum m_actions;
	map<State, int> m_utilityMap;
	map<State, Action> m_policyMap;

	bool zeroInitializeStateSpace();
	bool zeroInitializeActionSpace();
	bool zeroInitializeStateTransitionMap(const Action FIRST, const Action LAST);
	bool zeroInitializeRewardMap();
	bool zeroInitializeUtilityMap();

public:
	MDP();
	~MDP();
	map<State, int>	getUtilityMap();
	map<State, float> getRewardMap();
	map<State, Action> getPolicyMap();
	set <State> getStateSpace();
	
	void valueIteration(float discount);
	void policyIteration();
};

#endif // !MDP_H



