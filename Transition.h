#ifndef TRANSITION_H
#define TRANSITION_H

#include "State.h"

class Transition {
private:
	State m_fromState;
	State m_toState;
	int m_withAction;
public:
	Transition();
	Transition(State fromState, State toState, int withAction);
	~Transition();

	friend bool operator < (const Transition &t1, const Transition &t2);

	State getFromState();
	State getToState();
	int getAction();
};

#endif // !TRANSITION_H