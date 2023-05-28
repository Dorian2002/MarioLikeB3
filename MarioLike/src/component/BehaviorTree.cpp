#include "component/BehaviorTree.h"

BehaviorTree::~BehaviorTree()
{
	delete m_rootNode;
	m_rootNode = nullptr;
}
