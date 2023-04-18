#pragma once
#include <vector>
#include "utils/Rtti.h"

class Animation : public Rtti
{
public:
	DEFINE_RTTI(Animation)
	bool GetIsPlaying();
private:
	bool m_isPlaying;
};