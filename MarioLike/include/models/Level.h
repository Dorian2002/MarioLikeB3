#pragma once
#include "models/GameObject.h"
#include "models/Entity.h"
#include <utils/Vector2.h>
#include <component/BoxColliderComponent.h>
class Level : public GameObject
{
public:
	Level();
	~Level() = default;
	bool LoadLevel(const std::string _fileNameFront,const std::string _fileNameBack);
	int m_levelSize = 0;
};

