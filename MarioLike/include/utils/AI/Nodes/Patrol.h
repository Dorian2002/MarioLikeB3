#pragma once
#include <component/BehaviorTree.h>
#include <utils/AI/Node.h>
#include <models/Ennemy.h>

class Patrol : public Node {
public:
	Patrol(Ennemy* host) {
		m_host = host;
		m_direction = 1;
	}
	NodeState Evaluate() override {
		if (m_direction == 1) {
			if (!m_host->MoveRight()) {
				m_direction = -1;
			}
		}
		else {
			if (!m_host->MoveLeft()) {
				m_direction = 1;
			}
		}
		m_state = RUNNING;
		return m_state;
	}
private:
	Ennemy* m_host;
	int m_direction;
};
