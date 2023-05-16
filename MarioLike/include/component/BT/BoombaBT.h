#pragma once
#include <component/BehaviorTree.h>
#include <utils/AI/Nodes/Patrol.h>

class BoombaBT : public BehaviorTree {
public:
	BoombaBT(Ennemy* host) {
		m_rootNode = SetUpTree(host);
	};
	Node* SetUpTree(Ennemy* host) override {
		Node* m_rootNode = new Patrol(host);
		return m_rootNode;
	}
};

