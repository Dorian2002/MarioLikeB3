#pragma once
#include "Link.h"

class Animation
{
public:
	std::vector<Link*> GetLinks() {
		return m_outLinks;
	}
	bool GetIsPlaying() {
		return m_isPlaying;
	}
private:
	bool m_isPlaying;
	std::vector<Link*> m_outLinks;
};