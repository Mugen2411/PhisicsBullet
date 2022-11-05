#pragma once
#include "CCosutumeBase.h"
#include <string>
#include <vector>
#include <memory>

class CMover_Player;

class CCostumeFactory {
	std::vector<std::shared_ptr<CCostumeBase>> list;
	void Register(CCostumeBase* f);
	int cx;
	int cy;

public:
	CCostumeFactory();
	CCostumeBase* create(std::string);
};