#include "CObjectNode.h"

void CObjectNode::add_node(std::shared_ptr<CObjectNode> obj)
{
	objlist.push_back(obj);
}

std::vector<std::shared_ptr<CObjectNode>> CObjectNode::getList()
{
	std::vector<std::shared_ptr<CObjectNode>> retlist = objlist;
	
	for (auto itr = objlist.begin(); itr != objlist.end(); itr++) {
		std::vector<std::shared_ptr<CObjectNode>> list = (*itr)->getList();
		retlist.insert(retlist.end(), list.begin(), list.end());
	}
	return retlist;
}

CObjectNode::CObjectNode()
{
}

CObjectNode::~CObjectNode()
{
}
