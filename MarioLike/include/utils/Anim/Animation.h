#pragma once
#include <vector>
#include "utils/Rtti.h"
#include <SFML/Graphics/Sprite.hpp>

class Animation : public Rtti
{
public:
	DEFINE_RTTI(Animation)
	bool GetIsPlaying();
	Animation(sf::Texture*, int);
	~Animation();
	sf::Texture* GetTexture();
	float GetFrameTime();
	int GetFrameNumber();
private:
	bool m_isPlaying;
	sf::Texture* m_texture;
	int m_frameNumber;
	float m_frameTime;
};