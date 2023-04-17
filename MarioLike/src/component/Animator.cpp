#include "component/Animator.h"

void Animator::Play(Animation* anim)
{
	if (!anim->GetIsPlaying()) {
		//Play the animation
	}
}

void Animator::Update(float)
{
	CheckState();
	Play(m_currentState);
}

void Animator::Start()
{
}

void Animator::CheckState()
{
	for (Link* link : GetLinksWithOrigin(m_currentState)) {
		if (link->CheckCondition()) {
			m_currentState = link->GetTarget();
			return;
		}
	}
}

std::vector<Link*> Animator::GetLinksWithOrigin(Animation* originAnim)
{
	std::vector<Link*> animLinks = std::vector<Link*>();
	for (Link* link : m_Links) {
		if (originAnim->GetClassRttiName() == link->GetOrigin()->GetClassRttiName()) {
			animLinks.push_back(link);
		}
	}
	return animLinks;
}
