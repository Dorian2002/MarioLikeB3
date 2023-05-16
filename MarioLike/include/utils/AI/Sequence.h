#pragma once
#include <utils/AI/Node.h>

class Sequence : Node {
public: 
	Sequence() : Node() {}
	Sequence(std::vector<Node*> children) : Node(children) {}

	NodeState Evaluate() override {
		bool anyChildRunning = false;
		for (Node* node : m_children) {
			switch (node->Evaluate())
			{
			case FAILURE:
				m_state = FAILURE;
				return m_state;
			case SUCCESS:
				continue;
			case RUNNING:
				anyChildRunning = true;
				continue;
			default:
				m_state = SUCCESS;
				return m_state;
			}
		}
		m_state = anyChildRunning ? RUNNING : SUCCESS;
		return m_state;
	}
};
