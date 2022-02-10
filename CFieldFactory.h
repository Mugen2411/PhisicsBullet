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
	std::string getKey(int *n);
};

//以下マップチップの生成

std::shared_ptr<CField> LF_Grass(std::string name, CVector pos);
std::shared_ptr<CField> LF_IceFloor(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Tree(std::string name, CVector pos);

std::shared_ptr<CField> LF_Wall_Log(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Log_Burning(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_Log_Burned(std::string name, CVector pos);

std::shared_ptr<CField> LF_Wall_WoodFence(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_U(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_D(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_R(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_L(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UR(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UD(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_RL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_DR(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_DL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_URL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UDR(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_DRL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UDL(std::string name, CVector pos);
std::shared_ptr<CField> LF_Wall_WoodFence_UDRL(std::string name, CVector pos);