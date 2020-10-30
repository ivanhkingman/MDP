#pragma once

#include "environment.hpp"
#include "agent.hpp"

class GridWorld : public Environment {
    public:
        GridWorld();
        GridWorld(unsigned int dimension, int minReward, int maxReward, probability successRate);
        void reactToAction(action a);
        void executeMove(action moveDirection);
        
        void generateGridWorldTransitionMap();

        //! Display functions
        void display();
        void displayRewardMap();

        void reset();

    private:
        bool isOnUpperEdge(state state);
        bool isOnLeftEdge(state state);
        bool isOnLowerEdge(state state);
        bool isOnRightEdge(state state);
        bool isOnAnyEdge(state state);

        state getTileBelow(state fromState);
        state getTileAbove(state fromState);
        state getTileToLeft(state fromState);
        state getTileToRight(state fromState);

        action flipClockwize(action moveDirection);
        action flipCounterClockwize(action moveDirection);

        unsigned int m_dimension;
        probability m_moveSuccessRate;

};

void displayValueGrid(valueMap V);
void displayPolicyGrid(policy Pi);

template <typename T> 
bool isSquareSet(T set);

