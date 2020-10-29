#pragma once

using namespace std;

#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>

#include "mdp.hpp"
#include "algorithm.hpp"


enum actions {UP, DOWN, LEFT, RIGHT};

class Environment {
    public:
        Environment();
        ~Environment();

        virtual void reactToAction(action a);
        void generateRandomRewardMap(int from, int to);
        state getState();
        double giveReward();
        MDP stealMdp();

    protected:
        state m_state;
        stateSpace m_S;
        transitionMap m_T;
        actionSpace m_A;
        rewardMap m_R;
};


void fillIncompleteTransitionMap(transitionMap &T, actionSpace A, stateSpace S);
// Todo: Add function to verify axioms of probability for transition maps


