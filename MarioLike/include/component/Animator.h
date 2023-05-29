#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"
#include "utils/Anim/Link.h"
#include <utils/Sling.h>

class Animator : public Component
{
public:
	DEFINE_RTTI(Animator)
	void Update(float) override;
	void Start() override;
	Animator(Entity*, std::vector<Animation*>);
	~Animator();
	void CreateLink(Animation*, Animation*, Event::Signal<bool>*, bool, Event::SlotKey*);
	bool m_changeAnim;
private:
	int m_animIndex;
	float m_timer;
	std::vector<Animation*> m_states;
	Animation* m_currentState;
	void Play(Animation* anim);
	void CheckState();
	std::vector<Link*> m_links;
	std::vector<Link*> GetLinksWithOrigin(Animation* originAnim);
};

