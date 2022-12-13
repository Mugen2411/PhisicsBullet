#include "CFieldFactory.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Dirt.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Log.h"
#include "CField_Wall_WoodFence.h"
#include "CField_Wall_Vegetable.h"
#include "CField_Wall_Well.h"
#include "CField_Wall_DeepWater.h"
#include "CField_Wall_EnemySpawner.h"
#include "CField_Wall_PlayerSpawner.h"
#include "CField_Void.h"
#include "CField_Error.h"

void CFieldFactory::RegisterWall(CField* f)
{
	f->Move(CVector(wx * 32 + 16, wy * 32 + 16));
	wall_prototypes.push_back(std::unique_ptr<CField>(f));
	wx++;
	if (wx == 20) {
		wx = 0; wy++;
	}
}

void CFieldFactory::RegisterFloor(CField* f)
{
	f->Move(CVector(fx * 32 + 16, fy * 32 + 16));
	floor_prototypes.push_back(std::unique_ptr<CField>(f));
	fx++;
	if (fx == 20) {
		fx = 0; fy++;
	}
}

CFieldFactory::CFieldFactory()
{
	wx = 0;
	wy = 0;
	fx = 0;
	fy = 0;
	RegisterFloor(new CField_Grass("F_Grass", CVector()));
	RegisterFloor(new CField_IceFloor("F_Water", CVector(), 0));
	RegisterFloor(new CField_IceFloor("F_IceFloor", CVector(), -100));
	RegisterFloor(new CField_Dirt("F_Dirt", CVector(), 0));
	RegisterFloor(new CField_Dirt("F_Sand", CVector(), 1));

	RegisterWall(new CField_Wall_Tree("W_Tree", CVector()));
	RegisterWall(new CField_Wall_Log("W_Log", CVector(), 0));
	RegisterWall(new CField_Wall_Log("W_Log_Burning", CVector(), 1));
	RegisterWall(new CField_Wall_Log("W_Log_Burned", CVector(), 2));
	RegisterWall(new CField_Wall_Vegetable("W_Vegetable_carrot", CVector(), 0));
	RegisterWall(new CField_Wall_Vegetable("W_Vegetable_radish", CVector(), 1));
	RegisterWall(new CField_Wall_Well("W_Well", CVector()));

	RegisterWall(new CField_Wall_WoodFence("W_WoodFence", CVector(), 0));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_U", CVector(), 1));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_D", CVector(), 2));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_R", CVector(), 3));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_L", CVector(), 4));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UR", CVector(), 5));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UD", CVector(), 6));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UL", CVector(), 7));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_RL", CVector(), 8));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_DR", CVector(), 9));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_DL", CVector(), 10));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_URL", CVector(), 11));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UDR", CVector(), 12));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_DRL", CVector(), 13));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UDL", CVector(), 14));
	RegisterWall(new CField_Wall_WoodFence("W_WoodFence_UDRL", CVector(), 15));

	RegisterWall(new CField_Wall_DeepWater("W_DeepWater", CVector()));

	std::string buf;
	for (int i = 0; i < Constant::NumEnemySpawner; i++) {
		buf = "E" + std::to_string(i);
		RegisterWall(new CField_Wall_EnemySpawner(buf, CVector(), i));
	}
	RegisterWall(new CField_Wall_PlayerSpawner("P0", CVector()));

	RegisterWall(new CField_Void("W_Void", CVector()));
}

CField* CFieldFactory::create(int x, int y, std::string name)
{
	x *= 32;
	x += 16;
	y *= 32;
	y += 16;
	//ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
	if (name[0] == 'W' || name[0] == 'E' || name[0] == 'P') {
		auto itr = std::find_if(wall_prototypes.begin(), --wall_prototypes.end(), [name](std::unique_ptr<CField>& f) {return *f == name; });
		return ((*itr)->Clone(CVector(x, y)));
	}
	else {
		auto itr = std::find_if(floor_prototypes.begin(), --floor_prototypes.end(), [name](std::unique_ptr<CField>& f) {return *f == name; });
		return ((*itr)->Clone(CVector(x, y)));
	}
	
}

//category=0:Floor, 1:Wall
std::string CFieldFactory::getKey(int* n, int category)
{
	if (category == 1) {
		auto itr = wall_prototypes.begin();
		if (*n < 0) {
			*n = 0;
		}
		if (*n > wall_prototypes.size() - 1) {
			*n = wall_prototypes.size() - 1;
		}
		for (int i = 0; i < *n; i++) {
			itr++;
		}
		return (*itr)->getGID();
	}
	else {
		auto itr = floor_prototypes.begin();
		if (*n < 0) {
			*n = 0;
		}
		if (*n > floor_prototypes.size() - 1) {
			*n = floor_prototypes.size() - 1;
		}
		for (int i = 0; i < *n; i++) {
			itr++;
		}
		return (*itr)->getGID();
	}
	
	
}

void CFieldFactory::Render(int category) const
{
	switch (category) {
	case 0:
		for (const auto& p : floor_prototypes) {
			p->Render();
		}
		break;
	case 1:
		for (const auto& p : wall_prototypes) {
			p->Render();
		}
		break;
	}
	
}
