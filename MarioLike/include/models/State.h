#pragma once
class State
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void HandleInput() = 0;
};