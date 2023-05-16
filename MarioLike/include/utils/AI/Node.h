#pragma once
#include <vector>
#include <utils/BlackBoard/Blackboard.hpp>
#include <utils/BlackBoard/BlackboardID.hpp>
#include <string>

enum NodeState{
	RUNNING,
	SUCCESS,
	FAILURE
};

class Node {
public:
	Node* m_parent;
	Node() {
		m_parent = nullptr;
		m_state = SUCCESS;
	}
	Node(std::vector<Node*> children) {
		for (Node* node : children) {
			Attach(node);
		}
	}
	virtual NodeState Evaluate() {
		return FAILURE;
	}
	NodeState m_state;
	std::vector<Node*> m_children;
private:
	Container::Blackboard<int, bool, std::string> blackboard;
	void Attach(Node* node) {
		node->m_parent = this;
		m_children.push_back(node);
	}
};
