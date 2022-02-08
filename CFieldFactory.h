#pragma once
#include "CField.h"
#include <string>
#include <map>

class CFieldFactory
{
private:
	std::map<std::string, std::shared_ptr<CField>(*)(std::string name, CVector pos), std::less<>> loaderList;

public:
	CFieldFactory();
	std::shared_ptr<CField> create(int x, int y, std::string name);
};

std::shared_ptr<CField> LF_Grass(std::string name, CVector pos);
std::shared_ptr<CField> LF_IceFloor(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Tree(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Log(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Log_Burning(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Log_Burned(std::string name, CVector pos);