#ifndef STATE_H
#define STATE_H

#include <vector>
using namespace std;
using Ation = int;

class State
{
private:
	friend class Transition;
	const vector <float> m_state;
	unsigned int m_dimension;
public:
	State();
	State(vector<float> state);
	~State();
	vector<float> getState();
	int getDimension();

	friend bool operator< (const State &st1, const State &st2);
	friend bool operator == (const State &st1, const State &st2);
	friend bool operator != (const State &st1, const State &st2);

};

#endif // !STATE_H