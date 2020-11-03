#pragma once

#include <vector>
#include <random>
#include <ctime>

#include "environment.hpp"
#include "mdp.hpp"


using namespace std;

using state = vector<int>;
using action = int;


class Agent {
public:
    Agent();
    ~Agent();

    void executeAction(action action);
    void collectReward();
    void observeState();
    void printStateEstimate();
    void invokeAlgorithm();

    state getStateEstimate();
    double getReward();
    float getPreviousReward();
    Environment getEnvironment();
    policy getPolicy();
    valueMap getValueMap();
    MDP getMdp();

    void followPolicy();
    void updatePolicy(state s, action a);
    

    void deployInEnvironment(Environment &environment);
    void attatchAlgorithm();
    void setMDP(MDP mdp);
    void setValueMap(valueMap V);
    void setQValueMap(stateActionValueMap Q);
    void setPolicy(policy Pi);
    void reset();

protected:
    Environment* m_environment;
    state m_stateEstimate;
    MDP m_mdp;
    policy m_Pi;
    valueMap m_V;
    stateActionValueMap m_Q;
    int m_n;

    double m_totalReward;
    double m_previousReward;
};