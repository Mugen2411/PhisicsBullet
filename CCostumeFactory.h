#pragma once
#include "CCosutumeBase.h"
#include <string>

class CMover_Player;

class CCostumeFactory {
public:
	CCostumeBase* create(std::string, CMover_Player*);
};