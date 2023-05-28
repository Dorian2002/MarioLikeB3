#include "utils/AI/Node.h"

Node::Node()
{
	m_parent = nullptr;
	m_state = SUCCESS;
}

Node::Node(std::vector<Node*> children)
{
	for (Node* node : children) {
		Attach(node);
	}
}

Node::~Node()
{
	m_parent = nullptr;
	for (std::size_t i = 0; i < m_children.size(); i++)
	{
		delete m_children[i];
	}
	m_children.clear();
}

NodeState Node::Evaluate()
{
	return FAILURE;
}

void Node::Attach(Node* node)
{
	node->m_parent = this;
	m_children.push_back(node);
}
