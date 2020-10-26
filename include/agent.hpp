#include <vector>
#include "mdp.hpp"

using namespace std;

using state = vector<int>;
using action = int;

class Agent {
public:
    Agent();
    ~Agent();

    void attemptMove(action moveDirection);
    void executeMove(action moveDirection);
    state getPosition();
    

private:
    state m_state;
    MDP m_mdp;
};