#pragma once
#include "CEffect.h"
#include <vector>
#include <memory>

class CEffectParent
{
	static std::vector<std::shared_ptr<CEffect>> effectlist;
public:
	static void RegisterEffect(std::shared_ptr<CEffect> e);
	static void Reset();
	static void Update();
	static void Render();
};

