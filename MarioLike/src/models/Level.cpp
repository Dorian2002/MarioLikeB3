#include "models/Level.h"
#include "models/Background.h"
#include <iostream>
#include <fstream>
#include "models/Player.h"
#include <iostream>
#include <random>
#include <cmath>
#include <models/Block.h>
#include <models/Coin.h>
#include <models/Void.h>
#include <models/Finish.h>
#include "managers/EntityManager.h"
#include "models/Boomba.h"
#include "models/Finish.h"

Level::Level()
{

}

bool Level::LoadLevel(const std::string _fileNameFront, const std::string _fileNameBack)
{
	std::ifstream fileFront(_fileNameFront, std::ios_base::in);
	if (fileFront.is_open())
	{
		std::string line;
		unsigned int row = 0;
		unsigned int column = 0;
		float tileSize = 64.f;
		std::vector<Vec2u> emptyPos;

		while (std::getline(fileFront, line))
		{
			column = 0;

			for (auto& c : line)
			{
				Vec2u position = { column, row };

					switch (c)
					{
					case '1':
					{
						EntityManager::GetInstance()->AddEntity(new Block(position));
						/*Block* entity = new Block(position);
						rowEntities.emplace_back(entity);
						m_colliders.push_back(entity->GetComponent<BoxColliderComponent>());*/
						//entity->GetComponent<Transform>()->Scale(Vec2f{ 64.0f, 64.0f });
						break;
					}
					case '3':
					{
						EntityManager::GetInstance()->AddEntity(new Coin(position));
						/*Coin* entity = new Coin(position);
						rowEntities.emplace_back(entity);
						m_colliders.push_back(entity->GetComponent<BoxColliderComponent>());*/
						break;
					}
					case '4':
						EntityManager::GetInstance()->AddEntity(new Boomba(position));
						break;
					case '5':
						EntityManager::GetInstance()->AddEntity(new Finish(position));
						break;
					default:
					{
						break;
					}
					}
					column++;
			}
			if(column > m_levelSize)
			{
				m_levelSize = column;
			}
			row++;
		}
		fileFront.close();
		return true;
	}
	return false;
}
