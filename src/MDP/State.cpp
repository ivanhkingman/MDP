#include "State.h"

State::State() {

}

State::State(vector<float> state) : m_state(state), m_dimension(state.size()) {

}

State::~State() {

}

vector<float> State::getState() { 
	return m_state; 
}

int State::getDimension() { 
	return m_dimension; 
}

bool operator< (const State &st1, const State &st2) {
	return (st1.m_state < st2.m_state);
}

bool operator == (const State &st1, const State &st2) {
	return (st1.m_state == st2.m_state);
}

bool operator != (const State &st1, const State &st2) {
	return !(st1.m_state == st2.m_state);
}