#include "CEffectParent.h"

std::vector<std::shared_ptr<CEffect>> CEffectParent::effectlist;

void CEffectParent::RegisterEffect(std::shared_ptr<CEffect> e)
{
	effectlist.push_back(e);
}

void CEffectParent::Reset()
{
	effectlist.clear();
}

void CEffectParent::Update()
{
	for (std::shared_ptr<CEffect> v : CEffectParent::effectlist) {
		v->Update();
	}
	auto new_end = std::remove_if(effectlist.begin(), effectlist.end(), [](std::shared_ptr<CEffect> v)->bool {return !(*v); });
	effectlist.erase(new_end, effectlist.end());
}

void CEffectParent::Render()
{
	for (std::shared_ptr<CEffect> v : CEffectParent::effectlist) {
		v->Render();
	}
}