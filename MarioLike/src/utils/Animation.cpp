#include "utils/Anim/Animation.h"

bool Animation::GetIsPlaying()
{
	return m_isPlaying;
}

Animation::Animation(sf::Texture* texture, int frames)
{
	m_texture = texture; 
	m_frameNumber = frames;
	m_isPlaying = false;
	m_frameTime = 0.1f;
}

Animation::~Animation()
{
	m_texture = nullptr;
}

sf::Texture* Animation::GetTexture()
{
	return m_texture;
}

float Animation::GetFrameTime()
{
	return m_frameTime;
}

int Animation::GetFrameNumber()
{
	return m_frameNumber;
}
