#include "MDP.h"

MDP::MDP() {
	
}

MDP::~MDP() {

}

map<State, int>	MDP::getUtilityMap() { 
	return m_utilityMap; 
}

map<State, float> MDP::getRewardMap() { 
	return m_rewardMap;
}

map<State, Action> MDP::getPolicyMap() { 
	return m_policyMap; 
}

set <State> MDP::getStateSpace() { 
	return m_states;
}

bool MDP::zeroInitializeStateSpace() {
	State initialState;
	m_states.insert(initialState);
	return true;
}

bool MDP::zeroInitializeActionSpace() {
	m_actions{};
	return true;
}

bool MDP::zeroInitializeStateTransitionMap(const Action FIRST, const Action LAST) {
	for (auto fromState = m_states.begin(); fromState != m_states.end(); fromState++) {
		for (auto toState = m_states.begin(); toState != m_states.end(); toState++) {
			for (Action withAction = FIRST; withAction == LAST; withAction++) {
				Transition transition(*fromState, *toState, withAction);
				m_stateTransitionMap.insert(transition, 0);
			}
		}
	}
	return true;
}

bool MDP::zeroInitializeRewardMap() {
	for (auto it = m_rewardMap.begin(); it != m_rewardMap.end(); it++) {
		it->second = 0;
	}
	return true;
}

bool MDP::zeroInitializeUtilityMap() {
	for (auto it = m_utilityMap.begin(); it != m_utilityMap.end(); it++) {
		it->second = 0;
	}
	return true;
}

void MDP::valueIteration(float discount) {
	// Todo: Implement value iteration
}

void MDP::policyIteration() {
	// Todo: Implement policy iteration
}