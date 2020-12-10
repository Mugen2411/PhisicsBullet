#pragma once
#include <vector>
#include <memory>

class CObjectNode
{
protected:
	std::vector<std::shared_ptr<CObjectNode>> objlist;
	void add_node(std::shared_ptr<CObjectNode>);
	std::vector<std::shared_ptr<CObjectNode>> getList();
public:
	CObjectNode();
	virtual ~CObjectNode();
};

