#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Log.h"
#include "CField_Wall_WoodFence.h"

CFieldFactory::CFieldFactory()
{
	loaderList["Field_Grass"] = LF_Grass;
	loaderList["Field_IceFloor"] = LF_IceFloor;
	loaderList["Field_Wall_Tree"] = LF_Wall_Tree;

	loaderList["Field_Wall_Log"] = LF_Wall_Log;
	loaderList["Field_Wall_Log_Burning"] = LF_Wall_Log_Burning;
	loaderList["Field_Wall_Log_Burned"] = LF_Wall_Log_Burned;

	loaderList["Field_Wall_WoodFence"] = LF_Wall_WoodFence;
	loaderList["Field_Wall_WoodFence_U"] = LF_Wall_WoodFence_U;
	loaderList["Field_Wall_WoodFence_D"] = LF_Wall_WoodFence_D;
	loaderList["Field_Wall_WoodFence_R"] = LF_Wall_WoodFence_R;
	loaderList["Field_Wall_WoodFence_L"] = LF_Wall_WoodFence_L;
	loaderList["Field_Wall_WoodFence_UR"] = LF_Wall_WoodFence_UR;
	loaderList["Field_Wall_WoodFence_UD"] = LF_Wall_WoodFence_UD;
	loaderList["Field_Wall_WoodFence_UL"] = LF_Wall_WoodFence_UL;
	loaderList["Field_Wall_WoodFence_RL"] = LF_Wall_WoodFence_RL;
	loaderList["Field_Wall_WoodFence_DR"] = LF_Wall_WoodFence_DR;
	loaderList["Field_Wall_WoodFence_DL"] = LF_Wall_WoodFence_DL;
	loaderList["Field_Wall_WoodFence_URL"] = LF_Wall_WoodFence_URL;
	loaderList["Field_Wall_WoodFence_UDR"] = LF_Wall_WoodFence_UDR;
	loaderList["Field_Wall_WoodFence_DRL"] = LF_Wall_WoodFence_DRL;
	loaderList["Field_Wall_WoodFence_UDL"] = LF_Wall_WoodFence_UDL;
	loaderList["Field_Wall_WoodFence_UDRL"] = LF_Wall_WoodFence_UDRL;
}

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name)
{
	x *= 32;
	x += 16;
	y *= 32;
	y += 16;
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	auto r = loaderList.find(name);
	if (r == loaderList.end())return loaderList["error"]("error", CVector(x, y));
	return loaderList[name](name, CVector(x, y));
}

std::string CFieldFactory::getKey(int *n)
{
	auto itr = loaderList.begin();
	if (*n < 0) {
		*n = 0;
	}
	if (*n > loaderList.size()-1) {
		*n = loaderList.size()-1;
	}
	for (int i = 0; i < *n; i++) {
		itr++;
	}
	return itr->first;
}

std::shared_ptr<CField> LF_Grass(std::string name, CVector pos)
{
	return std::make_shared<CField_Grass>(name, pos);
}

std::shared_ptr<CField> LF_IceFloor(std::string name, CVector pos)
{
	return std::make_shared<CField_IceFloor>(name, pos, -100);
}

std::shared_ptr<CField> LF_Wall_Tree(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_Tree>(name, pos);
}

std::shared_ptr<CField> LF_Wall_Log(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_Log>(name, pos, 0);
}

std::shared_ptr<CField> LF_Wall_Log_Burning(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_Log>(name, pos, 1);
}

std::shared_ptr<CField> LF_Wall_Log_Burned(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_Log>(name, pos, 2);
}

static const int WOODFENCE = 8;

std::shared_ptr<CField> LF_Wall_WoodFence(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 0);
}

std::shared_ptr<CField> LF_Wall_WoodFence_U(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 1);
}

std::shared_ptr<CField> LF_Wall_WoodFence_D(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 2);
}

std::shared_ptr<CField> LF_Wall_WoodFence_R(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 3);;
}

std::shared_ptr<CField> LF_Wall_WoodFence_L(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 4);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UR(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 5);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UD(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 6);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 7);
}

std::shared_ptr<CField> LF_Wall_WoodFence_RL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 8);
}

std::shared_ptr<CField> LF_Wall_WoodFence_DR(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 9);
}

std::shared_ptr<CField> LF_Wall_WoodFence_DL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 10);
}

std::shared_ptr<CField> LF_Wall_WoodFence_URL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 11);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UDR(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 12);
}

std::shared_ptr<CField> LF_Wall_WoodFence_DRL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 13);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UDL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 14);
}

std::shared_ptr<CField> LF_Wall_WoodFence_UDRL(std::string name, CVector pos)
{
	return std::make_shared<CField_Wall_WoodFence>(name, pos, 15);
}
