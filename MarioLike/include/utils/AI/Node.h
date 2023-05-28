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
	Node();
	Node(std::vector<Node*> children);
	~Node();
	virtual NodeState Evaluate();
	NodeState m_state;
	std::vector<Node*> m_children;
private:
	Container::Blackboard<int, bool, std::string> blackboard;
	void Attach(Node* node);
};
