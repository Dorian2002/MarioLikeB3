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

Link::Link(Animation* origin, Animation* target, Event::Signal<bool>* sig, bool toValidate)
{
	m_origin = origin;
	m_target = target;
	m_sig = sig;
	m_toValidate = toValidate;
}

