#pragma once

#include "algorithm.hpp"

class ValueIteration : public Algorithm {
    public:
        ValueIteration();
        ValueIteration(MDP mdp, float gamma, float threshold);
        virtual ~ValueIteration();
        valueMap runWithoutAgent();
        void run();
        void derivePolicyFromValueMap();
        
    private:
        
        bool verifyOwnerMatch(Agent agent);
        MDP m_mdp;
        valueMap m_V;
        float m_gamma;
        float m_threshold;
};


policy derivePolicyFromValueMap(valueMap V);
void printValueMap(valueMap V);
