#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name, std::vector<double> params)
{
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	if (name == "Field_Grass")return std::make_shared<CField_Grass>("Field_Grass", CVector(x, y));
	if (name == "Field_IceFloor")return std::make_shared<CField_IceFloor>("Field_IceFloor", CVector(x, y), params[0]);
}
