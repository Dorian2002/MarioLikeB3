#pragma once

#include <string>
#include "models/Level.h"

class LevelManager
{
public:
	LevelManager();
	virtual ~LevelManager();
	LevelManager(LevelManager& _other) = delete;
	void operator=(const LevelManager& _other) = delete;
	static LevelManager* GetInstance();
	Level* LoadLevel();
	void RenderLevel();
	Level* GetLevel();

private:
	static LevelManager* m_instance;
	Level* m_level;
};
