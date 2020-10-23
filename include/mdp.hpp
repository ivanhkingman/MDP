#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "transition.hpp"

using namespace std;

using state = vector<int>;
using probability = double;
using action = int;
using reward = int;

using stateSpace = set<state>;
using transitionMap = map<int, probability>;
using actionSpace = set<action>;
using rewardMap = map<state, reward>;

class MDP {
public:
    MDP();
    MDP(stateSpace S, transitionMap T, actionSpace A, rewardMap R);
    ~MDP();

    stateSpace getStateSpace();
    transitionMap getTransitionMap();
    actionSpace getActionSpace();
    rewardMap getRewardMap();

    void setStateSpace(stateSpace S);
    void setTransitionMap(transitionMap T);
    void setActionSpace(actionSpace A);
    void setRewardMap(rewardMap R);

    void printStateSpace();
    void printTransitionMap();
    void printActionSpace();
    void printRewardMap();
    void print();

private:
    
    transitionMap m_T;
    rewardMap m_R;
    stateSpace m_S;
    actionSpace m_A;
    
};