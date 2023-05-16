#include "component/Animator.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <models/Entity.h>
#include <component/SpriteComponent.h>

void Animator::Play(Animation* anim)
{
	sf::Texture* texture = anim->GetTexture();
	auto spriteComponent = m_root->GetComponent<SpriteComponent>();
	if (m_changeAnim) {
		spriteComponent->m_sprite->setTexture(*texture);
		spriteComponent->m_sprite->setTextureRect(sf::IntRect(0, 0, spriteComponent->m_spriteSize.x, spriteComponent->m_spriteSize.y));
		Timer = 0;
		m_animIndex = 0;
	}
	else {
		if (Timer >= anim->GetFrameTime()) {
			Timer = 0;
			if (m_animIndex == anim->GetFrameNumber()) {
				spriteComponent->m_sprite->setTextureRect(sf::IntRect(0, 0, spriteComponent->m_spriteSize.x, spriteComponent->m_spriteSize.y));
				m_animIndex = 0;
			}
			else {
				spriteComponent->m_sprite->setTextureRect(sf::IntRect(m_animIndex * spriteComponent->m_spriteSize.x, 0, spriteComponent->m_spriteSize.x, spriteComponent->m_spriteSize.y));
				m_animIndex += 1;
			}
		}
	}
}

void Animator::Update(float deltaT)
{
	Timer += deltaT*1000;
	CheckState();
	Play(m_currentState);
}

void Animator::Start()
{
}

void Animator::CreateLink(Animation* anim1, Animation* anim2, Event::Signal<bool>* sig, bool val)
{
	m_links.push_back(new Link(anim1, anim2, sig, val));
}

Animator::Animator(Entity* root, std::vector<Animation*> states)
{
	Timer = 0;
	m_root = root;
	m_states = states;
	m_links = std::vector<Link*>();
	m_changeAnim = false;
	m_animIndex = 0;
	for (Animation* state : m_states) {
		if (state->GetClassRttiName().find("Idle") != std::string::npos) {
			m_currentState = state;
		}
		else {
			m_currentState = m_states[0];
		}
	}
}

void Animator::CheckState()
{
	m_changeAnim = false;
	for (Link* link : GetLinksWithOrigin(m_currentState)) {
		link->CheckCondition();
		if (m_changeAnim == true) {
			m_currentState = link->GetTarget();
			return;
		}
	}
}

std::vector<Link*> Animator::GetLinksWithOrigin(Animation* originAnim)
{
	std::vector<Link*> animLinks = std::vector<Link*>();
	for (Link* link : m_links) {
		if (originAnim->GetClassRttiName() == link->GetOrigin()->GetClassRttiName()) {
			animLinks.push_back(link);
		}
	}
	return animLinks;
}
