#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"
#include "utils/Anim/Link.h"

class Animator : Component
{
public:
	DEFINE_RTTI(Animator)
	void Update(float) override;
	void Start() override;
private:
	struct Data{};
	std::vector<Animation*> m_states;
	Animation* m_currentState;
	void Play(Animation* anim);
	void CheckState();
	std::vector<Link*> m_Links;
	std::vector<Link*> GetLinksWithOrigin(Animation* originAnim);
};

