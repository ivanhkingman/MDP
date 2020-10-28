#pragma once

#include <vector>
#include <random>
#include <ctime>

#include "utils.hpp"
#include "mdp.hpp"
#include "algorithms.hpp"

using namespace std;

using state = vector<int>;
using action = int;

class Agent {
public:
    Agent();
    ~Agent();

    void attemptMove(action moveDirection, double SUCCESS, int dim);
    void executeMove(action moveDirection, int dim);
    void collectReward();
    void displayPosition();
    state getPosition();
    double getReward();
    
    void setMDP(MDP mdp);
    void reset();


private:
    state m_state;
    MDP m_mdp;
    double m_totalReward;
};