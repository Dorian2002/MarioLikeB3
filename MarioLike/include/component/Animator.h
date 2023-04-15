#pragma once
#include "models/Component.h"
#include <vector>
#include "utils/Anim/Animation.h"

class Animator : Component
{
public:
	DEFINE_RTTI(Animator);

private:
	std::vector<Animation*> m_states;
	Animation* m_currentState;
	void Play(Animation* anim) {
		if (!anim->GetIsPlaying()) {

		}
	}
	void Update(float) override {
		CheckState();
		Play(m_currentState);
	}
	void Start() override {

	}
	void CheckState() {
		for (Link* link : m_currentState->GetLinks()) {
			if (link->CheckCondition()); {
				m_currentState = link->GetTarget();
				return;
			}
		}
	}
};

