#pragma once
#include "utils/Anim/Animation.h"
#include "utils/Sling.h"

class Link
{
public:
	void CheckCondition();
	Animation* GetTarget();
	Animation* GetOrigin();
	Link(Animation*, Animation*, Event::Signal<bool>*, bool, Event::SlotKey*);
	~Link();
private:
	Event::Signal<bool>* m_sig;
	Animation* m_origin;
	Animation* m_target;
	bool m_toValidate;
	Event::SlotKey* m_key;
};