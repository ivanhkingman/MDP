#include <vector>
#include "utils.hpp"

using namespace std;

using state = vector<int>;
using action = int;

class Agent {
public:
    Agent();
    ~Agent();

    void attemptMove(action moveDirection);
    void executeMove(action moveDirection);
    void collectReward();
    void printPosition();
    state getPosition();
    
    void setMDP(MDP mdp);

private:
    state m_state;
    MDP m_mdp;
    int m_totalReward;
};