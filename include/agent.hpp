#pragma once

#include <vector>
#include <random>
#include <ctime>

#include "environment.hpp"
#include "mdp.hpp"
#include "algorithm.hpp"

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
    Environment getEnvironment();
    policy getPolicy();

    void followPolicy();
    
    void deployInEnvironment(Environment environment);
    void attatchAlgorithm(Algorithm &algorithm);
    void setMDP(MDP mdp);
    void reset();

private:
    state m_stateEstimate;
    MDP m_mdp;
    policy m_Pi;
    valueMap m_V;
    stateActionValueMap m_Q;
    int m_n;

    Environment m_environment;
    Algorithm m_algorithm;

    double m_totalReward;
};