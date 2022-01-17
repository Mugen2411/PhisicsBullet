#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Log.h"

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name)
{
	x *= 32;
	x += 16;
	y *= 32;
	y += 16;
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	if (name == "Field_Grass")		return std::make_shared<CField_Grass>(name, CVector(x, y));
	if (name == "Field_IceFloor")	return std::make_shared<CField_IceFloor>(name, CVector(x, y), -100);
	if (name == "Field_Wall_Tree")	return std::make_shared<CField_Wall_Tree>(name, CVector(x, y));
	if (name == "Field_Wall_Log")	return std::make_shared<CField_Wall_Log>(name, CVector(x, y), 0);
	if (name == "Field_Wall_Log_Burning")	return std::make_shared<CField_Wall_Log>(name, CVector(x, y), 1);
	if (name == "Field_Wall_Log_Burned")	return std::make_shared<CField_Wall_Log>(name, CVector(x, y), 2);
}
