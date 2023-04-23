#pragma once
#include "models/State.h"
#include <vector>
class StateManager
{
public:
	void pushState(State* state);
	void popState();
	State* CurrentState();
private:
	std::vector<State*> m_states;
};

