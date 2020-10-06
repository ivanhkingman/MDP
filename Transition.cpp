#include "Transition.h"


Transition::Transition() {

}

Transition::Transition(State toState, State fromState, int withAction)
	: m_fromState(fromState), m_toState(toState), m_withAction(withAction) {

};

Transition::~Transition() {

}

bool operator < (const Transition &t1, const Transition &t2) {
	if (t1.m_fromState != t2.m_fromState) {
		return t1.m_fromState < t2.m_fromState;
	}
	if (t1.m_toState != t2.m_toState) {
		return t2.m_toState < t2.m_toState;
	}
	else { return t1.m_withAction < t2.m_withAction; };

}