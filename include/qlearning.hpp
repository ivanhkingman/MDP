# pragma once

#include "algorithm.hpp"

class QLearning : public Algorithm {
    public:
        QLearning();
        QLearning(stateSpace S, actionSpace A,
                    bool terminateByCount, unsigned int numEpisodes, double alpha, double gamma, double epsilon,
                    unsigned int terminationCount);
        ~QLearning();
        void run();
        bool isTerminal(state state);
    private:
        stateSpace m_S;
        actionSpace m_A;
        stateActionValueMap m_Q;
        stateSpace m_terminalStates; // Subset of m_S so that if the agent enters said state, the episode terminates
        bool m_episodeTerminateByCount;
        float m_epsilon;
        unsigned int m_numEpisodes;
        double m_alpha; // learning rate
        double m_gamma;
        int m_terminationCount;
        bool m_reachedGoalState = false;
};  