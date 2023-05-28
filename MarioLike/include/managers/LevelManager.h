#pragma once

#include <string>
#include "models/Level.h"
#include "models/Background.h"
#include "models/Player.h"

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
	void MoveLevel();

private:
	static LevelManager* m_instance;
	Level* m_level;
	Background* m_sky;
	Background* m_parallaxSky;
};
