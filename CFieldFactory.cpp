#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Log.h"

CFieldFactory::CFieldFactory()
{
	loaderList["Field_Grass"] = LF_Grass;
	loaderList["Field_IceFloor"] = LF_IceFloor;
	loaderList["Field_Wall_Tree"] = LF_Wall_Tree;
	loaderList["Field_Wall_Log"] = LF_Wall_Log;
	loaderList["Field_Wall_Log_Burning"] = LF_Wall_Log_Burning;
	loaderList["Field_Wall_Log_Burned"] = LF_Wall_Log_Burned;
}

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name)
{
	x *= 32;
	x += 16;
	y *= 32;
	y += 16;
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	return loaderList[name](name, CVector(x, y));
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
