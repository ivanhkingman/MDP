#include <vector>
#include <iostream>
#include <map>
#include <set>

using namespace std;

using state = vector<int>;
using action = int;
using action = int;
using reward = int;
using stateActionPair = pair<state, action>;
using probability = double;

class Transition {
public:
    Transition();
    Transition(state leavingState, state enteringState, action withAction);
    ~Transition();

    state getLeavingState();
    state getEnteringState();
    action getWithAction();

    void setLeavingState(state leavingState);
    void setEnteringState(state enteringState);
    void setWithAction(action withAction);

    void printLeavingState();
    void printEnteringState();
    void printWithAction();
    void print();

    friend bool operator < (const Transition &t1, const Transition &t2);

private:
    state m_leavingState;
    state m_enteringState;
    action m_withAction;
};

void printState(state state);

using stateSpace = set<state>;
using transitionMap = map<Transition, probability>;
using actionSpace = set<action>;
using rewardMap = map<state, reward>;
using valueMap = map<state, double>;
using policy = map<state, action>;
using stateActionValueMap = map<stateActionPair, double>;