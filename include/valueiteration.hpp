#pragma once

#include "algorithm.hpp"

class ValueIteration : public Algorithm {
    public:
        ValueIteration();
        ~ValueIteration();
        
        void run();
        valueMap runWithoutAgent();
        
    private:
        MDP m_mdp; 
        float m_gamma;
        float m_threshold;
        


};


policy derivePolicyFromValueMap(valueMap V);
void printValueMap(valueMap V);
valueMap zeroInitializeValueMap(stateSpace S);