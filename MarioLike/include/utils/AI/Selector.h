#pragma once
#include<utils/AI/Node.h>

class Selector : Node {
public:
	Selector() : Node() {}
	Selector(std::vector<Node*> children) : Node(children) {}

	NodeState Evaluate() override {
		for (Node* node : m_children) {
			switch (node->Evaluate())
			{
			case FAILURE:
				continue;
			case SUCCESS:
				m_state = SUCCESS;
				return m_state;
			case RUNNING:
				m_state = RUNNING;
				return m_state;
			default:
				m_state = SUCCESS;
				return m_state;
			}
		}
		m_state = FAILURE;
		return m_state;
	}
};
