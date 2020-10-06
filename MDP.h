#include <iostream>
#include "State.h"

#include <map>
#include <set>
#include <vector>

#ifndef _MDP_H_
#define _MDP_H_

using namespace		std;
using probability	= float;
using Action		= int;

template<typename T>
struct transition {
	State<T>	fromState;
	State<T>	toState;
	Action		withAction;
};

template<typename T>
class MDP {
private:

	// Fundamental MDP variables
	set<State<T>>					m_states;
	map<State<T>, float>			m_rewardMap;
	map<transition<T>, probability>	m_stateTransitionMap;
	enum							m_actions;

	// Associated with policy- and value iteration
	map<State<T>, int>				m_utilityMap;
	map<State<T>, Action>			m_policyMap;

	// Initialization routines
	bool zeroInitializeStateSpace() {
		State<T> initialState;
		m_states.insert(initialState);
		return true;
	};

	bool zeroInitializeActionSpace() {
		m_actions = {};
		return true;
	};

	bool zeroInitializeStateTransitionMap(const Action FIRST, const Action LAST) {
		for (auto fromState = m_states.begin(); m_states != m_states.end(); m_states++) {
			for (auto toState = m_states.begin(); m_states != m_states.end(); m_states++) {
				for (Action withAction = FIRST; withAction == LAST; withAction++) {
					transition transition = { *fromState<T>, *toState<T>, withAction };
					m_stateTransitionMap.insert(transition, 0);
				}
			}
		}
	};

	bool zeroInitializeRewardMap() {
		for (auto it = m_rewardMap.begin(); it != m_rewardMap.end(); it++) {
			it->second = 0;
		}
	};

	bool zeroInitializeUtilityMap() {
		for (auto it = m_utilityMap.begin(); it != m_utilityMap.end(); it++) {
			it->second = 0;
		}
	};

public:
	MDP() {

	};
	~MDP() {

	};
	map<State<T>, int>		getUtilityMap() { return m_utilityMap; };
	map<State<T>, float>	getRewardMap() { return m_rewardMap; };
	map<State<T>, Action>	getPolicyMap() { return m_policyMap; };
	set <State<T>>			getStateSpace() { return m_states };
	
	void valueIteration(float discount);
	void policyIteration();
	int	size();
};

#endif




