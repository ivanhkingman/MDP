# pragma once

#include "algorithm.hpp"

class PolicyIteration : public Algorithm {
    public:
        PolicyIteration();
        PolicyIteration(MDP mdp, double gamma, double threshold);
        virtual ~PolicyIteration();
        valueMap runWithoutAgent();
        void run();
        void policyEvaluation(policy Pi);
    private:
        bool verifyOwnerMatch(Agent agent);
        MDP m_mdp;
        valueMap m_V;
        policy m_Pi;
        float m_gamma;
        float m_threshold;
};