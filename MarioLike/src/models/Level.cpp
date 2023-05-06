#include "models/Level.h"
#include "models/Background.h"
#include <iostream>
#include <fstream>
#include "models/Player.h"
#include <iostream>
#include <random>
#include <cmath>
#include <models/Block.h>
#include <models/Void.h>

Level::Level()
{

}

bool Level::LoadLevel(const std::string _fileNameFront, const std::string _fileNameBack)
{
	std::ifstream fileFront(_fileNameFront, std::ios_base::in);
	if (fileFront.is_open())
	{
		std::cout << ">> File level is open" << std::endl;
		std::string line;
		unsigned int row = 0;
		unsigned int column = 0;
		float tileSize = 64.f;
		std::vector<Vec2u> emptyPos;

		while (std::getline(fileFront, line))
		{
			column = 0;
			std::vector<Entity*> rowEntities;

			for (auto& c : line)
			{
				Vec2u position = { column, row };

				switch (c)
				{
				case '1':
				{
					Block* entity = new Block(position);
					rowEntities.emplace_back(entity);
					//entity->GetComponent<Transform>()->Scale(Vec2f{ 64.0f, 64.0f });
					break;
				}
				default:
				{
					Void* entity = new Void();
					rowEntities.emplace_back(entity);
					break;
				}
				}

				column++;
			}
			m_map.emplace_back(rowEntities);
			row++;
		}
		fileFront.close();
		return true;
	}
	else
	{
		std::cout << ">> File level cannot be open !" << std::endl;
		return false;
	}
}

void Level::LoadBackground()
{
	Background* Sky = new Background({ 16,16 });
	RenderManager::GetInstance()->AddDrawCall(new DrawCall(Sky, 2));
}
