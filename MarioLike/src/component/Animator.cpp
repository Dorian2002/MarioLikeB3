#include "component/Animator.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <models/Entity.h>
#include <component/SpriteComponent.h>

void Animator::Play(Animation* anim)
{
	//Load texture and sprite
	sf::Texture* texture = anim->GetTexture();
	auto spriteComponent = m_root->GetComponent<SpriteComponent>();

	//If we have to change anim wee apply texture and rect then reset the timer and frame index
	if (m_changeAnim) {
		spriteComponent->m_sprite->setTexture(*texture);
		spriteComponent->m_sprite->setTextureRect(sf::IntRect(0, 0, spriteComponent->m_spriteSize.x, spriteComponent->m_spriteSize.y));
		m_timer = 0;
		m_animIndex = 0;
	}
	//Otherwise we check timer and if needed, reset it and change frame, also we manage last frame case
	else {
		if (m_timer >= anim->GetFrameTime()) {
			m_timer = 0;
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
	m_timer += deltaT;
	CheckState();
	Play(m_currentState);
}

void Animator::Start()
{
}

void Animator::CreateLink(Animation* anim1, Animation* anim2, Event::Signal<bool>* sig, bool val, Event::SlotKey* key)
{
	m_links.push_back(new Link(anim1, anim2, sig, val, key));
}

Animator::Animator(Entity* root, std::vector<Animation*> states)
{
	m_timer = 0;
	m_root = root;
	m_states = states;
	m_links = std::vector<Link*>();
	m_changeAnim = false;
	m_animIndex = 0;
	//We check if there is an Idle anim and if so, set it as current anim
	for (Animation* state : m_states) {
		if (state->GetClassRttiName().find("Idle") != std::string::npos) {
			m_currentState = state;
		}
		else {
			m_currentState = m_states[0];
		}
	}
}

Animator::~Animator()
{
	for (std::size_t i = 0; i < m_states.size(); i++)
	{
		delete m_states[i];
	}
	m_states.clear();
	for (std::size_t i = 0; i < m_links.size(); i++)
	{
		delete m_links[i];
	}
	m_links.clear();
}

void Animator::CheckState()
{
	//We loop on all links coming from current anim to others and check if we have to change or not
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
