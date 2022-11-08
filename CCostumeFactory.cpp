#include "CCostumeFactory.h"
#include "CCostume_Uniform.h"
#include "CCostume_Festa.h"
#include "CCostume_Archer_Flame.h"
#include <algorithm>

void CCostumeFactory::Register(CCostumeBase* f)
{
	list.push_back(std::shared_ptr<CCostumeBase>(f));
}

CCostumeFactory::CCostumeFactory()
{
	Register(new CCostume_Festa("C_Festa"));
	Register(new CCostume_Uniform("C_Uniform"));
	Register(new CCostume_Archer_Flame("C_Archer_Flame"));
}

CCostumeBase* CCostumeFactory::create(std::string GID)
{
	auto itr = std::find_if(list.begin(), --list.end(), [&](std::shared_ptr<CCostumeBase>& v) {return (*v).GID == GID; });
	return (*itr)->Clone();
}

CCostumeBase* CCostumeFactory::create(int idx)
{
	auto itr = list[idx];
	return itr->Clone();
}
