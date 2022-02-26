#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Log.h"
#include "CField_Wall_WoodFence.h"
#include "CField_Error.h"

void CFieldFactory::Register(CField* f)
{
	prototypes.push_back(std::shared_ptr<CField>(f));
}

CFieldFactory::CFieldFactory()
{
	Register(new CField_Grass("Field_Grass", CVector()));
	Register(new CField_IceFloor("Field_IceFloor", CVector(), -100));
	Register(new CField_Wall_Tree("Field_Wall_Tree", CVector()));

	Register(new CField_Wall_Log("Field_Wall_Log", CVector(), 0));
	Register(new CField_Wall_Log("Field_Wall_Log_Burning", CVector(), 1));
	Register(new CField_Wall_Log("Field_Wall_Log_Burned", CVector(), 2));
	
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence", CVector(), 0));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_U", CVector(), 1));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_D", CVector(), 2));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_R", CVector(), 3));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_L", CVector(), 4));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UR", CVector(), 5));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UD", CVector(), 6));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UL", CVector(), 7));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_RL", CVector(), 8));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_DR", CVector(), 9));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_DL", CVector(), 10));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_URL", CVector(), 11));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UDR", CVector(), 12));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_DRL", CVector(), 13));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UDL", CVector(), 14));
	Register(new CField_Wall_WoodFence("Field_Wall_WoodFence_UDRL", CVector(), 15));

	Register(new CField_Error("Field_Error", CVector()));
}

std::shared_ptr<CField> CFieldFactory::create(int x, int y, std::string name)
{
	x *= 32;
	x += 16;
	y *= 32;
	y += 16;
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	auto itr = std::find_if(prototypes.begin(), --prototypes.end(), [name](std::shared_ptr<CField>& f) {return *f == name; });
	return std::shared_ptr<CField>((*itr)->Clone(CVector(x, y)));
}

std::string CFieldFactory::getKey(int *n)
{
	auto itr = prototypes.begin();
	if (*n < 0) {
		*n = 0;
	}
	if (*n > prototypes.size()-1) {
		*n = prototypes.size()-1;
	}
	for (int i = 0; i < *n; i++) {
		itr++;
	}
	return (*itr)->getGID();
}