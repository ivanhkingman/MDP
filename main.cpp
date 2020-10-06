#include <iostream>
#include "MDP.h"
#include <set>

using namespace std;

int main()
{
	enum plankton {NO_PLANKTON = 0, SOME_PLANKTON = 1, ALOT_PLANKTON = 2};
	enum current {NO_CURRENT = 0, SOME_CURRENT = 1, ALOT_CURRENT = 2};
	enum maneuvers {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};

	State state1({ 1,2, SOME_CURRENT, NO_PLANKTON });
	State state2({ 2,2, NO_CURRENT, ALOT_PLANKTON });
	State state3({ 2,1, NO_CURRENT, NO_PLANKTON });

	Transition transition1(state1, state2, NORTH);
	Transition transition2(state1, state3, WEST);
	Transition transition3(state2, state3, SOUTH);

	set<Transition> myTransitionSet;
	myTransitionSet.insert(transition1);
	myTransitionSet.insert(transition2);
	myTransitionSet.insert(transition3);

	for (set<Transition>::iterator it = myTransitionSet.begin(); it != myTransitionSet.end(); it++) {
		Transition t = *it;
		cout << t.getAction() << endl;
	};


	return 0;
}