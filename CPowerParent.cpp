#include "CPowerParent.h"
#include "CPower.h"

CPowerParent::CPowerParent()
{
}

void CPowerParent::Add(std::shared_ptr<CPower> p)
{
	powerList.push_back(p);
}

void CPowerParent::Update()
{
}

void CPowerParent::Render()
{
}
