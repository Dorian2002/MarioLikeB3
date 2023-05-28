#include "utils/Anim/Link.h"

void Link::CheckCondition()
{
	m_sig->emit(m_toValidate);
}

Animation* Link::GetTarget() {
	return m_target;
}
Animation* Link::GetOrigin() {
	return m_origin;
}

Link::Link(Animation* origin, Animation* target, Event::Signal<bool>* sig, bool toValidate, Event::SlotKey* key)
{
	m_origin = origin;
	m_target = target;
	m_sig = sig;
	m_toValidate = toValidate;
	m_key = key;
}

Link::~Link()
{
	m_origin = nullptr;
	m_target = nullptr;
	m_sig->disconnect(*m_key);
	delete m_sig;
	m_sig = nullptr;
}

