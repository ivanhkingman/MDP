#include <iostream>
#include "Eigen\Dense"

using Eigen::Vector2f;

class Agent
{
public:
	Agent();
	~Agent();
	void moveAgent();
	void showAgentPosition();
private:
	Vector2f position;
};

