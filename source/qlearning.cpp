#include "qlearning.hpp"

QLearning::QLearning(){

}

QLearning::QLearning(stateSpace S, actionSpace A,
                    bool terminateByCount, unsigned int numEpisodes, double alpha, double gamma, double epsilon,
                    unsigned int terminationCount)
: m_S(S), m_A(A),  m_episodeTerminateByCount(terminateByCount),
    m_numEpisodes(numEpisodes), m_alpha(alpha), m_gamma(gamma), m_epsilon(epsilon), m_terminationCount(terminationCount) 
{

} 

QLearning::~QLearning() {}


void QLearning::run() {
    if (!m_hasOwner) {cout << "Q-Learning cannot run without an owner. Terminating." << endl; return; }
    stateActionValueMap Q = zeroInitializeQ(m_S, m_A);
    actionSpace A = m_owner->getMdp().getActionSpace();
    m_owner->setPolicy(zeroInitializePolicy(m_S));
    // Episode loop
    for (int e = 0; e < m_numEpisodes; e++) {
        // cout << "Episode: " << e << endl;
        state currentState = m_owner->getStateEstimate();
        bool m_reachedGoalState = false;
        int stateCount = 0;

        // Step loop
        bool exploit, explore;
        float diceRoll;
        while (!m_reachedGoalState) {
            // cout << "Step: " << stateCount << endl;
            // Choose action
            diceRoll = static_cast <float> (rand())/ static_cast <float> (RAND_MAX);
            // cout << "Dice-roll: " << diceRoll << endl;
            // cout << "Epsilon; " << m_epsilon << endl;

            if (diceRoll < m_epsilon) {
                exploit = true;
                explore = false;
            } else {
                exploit = false;
                explore = true;
            }

            action currentAction;
            if (exploit) {
                // cout << "Exploiting" << endl;
                double bestValue = -DBL_MAX;
                action bestAction;
                for (auto actionIt = m_A.begin(); actionIt != m_A.end(); actionIt++) {
                    action a = *actionIt;
                    stateActionPair stateAction(currentState, a);
                    double value = Q.at(stateAction);
                    if (value > bestValue) {bestValue = value; bestAction = a;}
                }
                m_owner->updatePolicy(currentState, bestAction);
                // cout << "Inserted action " << bestAction << " to state "; printState(currentState);
                // cout << endl;
                currentAction = bestAction;
            } else {
                // cout << "Exploring" << endl;
                currentAction = selectRandomAction(m_A);
            }

            // Take action and observe results
            // cout << "Executing action: " << currentAction << endl;
            m_owner->executeAction(currentAction);
            m_owner->collectReward();
            m_owner->observeState();
            double resultingReward = m_owner->getPreviousReward();
            state resultingState = m_owner->getStateEstimate();
            
            // Update action-value-map
            stateActionPair stateAction(currentState, currentAction);
            
            Q.at(stateAction) = Q.at(stateAction) + m_alpha*(resultingReward + m_gamma * maximizeValueOverActionAndState(Q, resultingState, A) - Q.at(stateAction));
            currentState = resultingState;

            stateCount++;

            // Check termination criterea
            if (m_episodeTerminateByCount) {
                m_reachedGoalState = (stateCount >= m_terminationCount);
            } else {
                m_reachedGoalState = isTerminal(currentState);
            }
        }
        m_owner->setQValueMap(Q);
    }
    return;
}

bool QLearning::isTerminal(state state) {
    if (m_terminalStates.find(state) == m_terminalStates.end()) {
        m_reachedGoalState == true;
        cout << "Agent reached terminal state" << endl;
        return true;
    } else {return false;}
}