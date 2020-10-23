#include <vector>
using namespace std;

using state = vector<int>;
using action = int;

class Transition {
public:
    Transition();
    Transition(state leavingState, state enteringState, action withAction);
    ~Transition();

    state getLeavingState();
    state getEnteringState();
    action getWithAction();

    void setLeavingState(state leavingState);
    void setEnteringState(state enteringState);
    void setWithAction(action withAction);

    void printLeavingState();
    void printEnteringState();
    void printWithAction();

    

private:
    state m_leavingState;
    state m_enteringState;
    action m_withAction;
};