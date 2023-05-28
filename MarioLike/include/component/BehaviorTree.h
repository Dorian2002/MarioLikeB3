#pragma once
#include <models/Component.h>
#include <utils/AI/Node.h>
#include <models/Ennemy.h>

class BehaviorTree : public Component{
public:
	Node* m_rootNode;
	BehaviorTree() {};
	BehaviorTree(Ennemy* host) {
		m_rootNode = SetUpTree(host);
	}
	~BehaviorTree();
	void Update(float) override {
		if (m_rootNode != nullptr) {
			m_rootNode->Evaluate();
		}
	}
	virtual Node* SetUpTree(Ennemy* host) = 0;
};
