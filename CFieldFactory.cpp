#include "CFieldFactory.h"

#include "CField_Cave.h"
#include "CField_Decoration_Light.h"
#include "CField_Decoration_Torch.h"
#include "CField_Dirt.h"
#include "CField_Error.h"
#include "CField_Grass.h"
#include "CField_IceFloor.h"
#include "CField_Lava.h"
#include "CField_Void.h"
#include "CField_Wall_Cave.h"
#include "CField_Wall_DeepWater.h"
#include "CField_Wall_EnemySpawner.h"
#include "CField_Wall_Log.h"
#include "CField_Wall_PlayerSpawner.h"
#include "CField_Wall_Rock.h"
#include "CField_Wall_Tree.h"
#include "CField_Wall_Vegetable.h"
#include "CField_Wall_Well.h"
#include "CField_Wall_WoodFence.h"

void CFieldFactory::RegisterWall(CField* f) {
  f->Move(CVector(wx_ * 32 + 16, wy_ * 32 + 16));
  wall_prototypes_.push_back(std::unique_ptr<CField>(f));
  wx_++;
  if (wx_ == 20) {
    wx_ = 0;
    wy_++;
  }
}

void CFieldFactory::RegisterFloor(CField* f) {
  f->Move(CVector(fx_ * 32 + 16, fy_ * 32 + 16));
  floor_prototypes_.push_back(std::unique_ptr<CField>(f));
  fx_++;
  if (fx_ == 20) {
    fx_ = 0;
    fy_++;
  }
}

CFieldFactory::CFieldFactory() {
  wx_ = 0;
  wy_ = 0;
  fx_ = 0;
  fy_ = 0;
  RegisterFloor(new CField_Grass("F_Grass", CVector()));
  RegisterFloor(new CField_IceFloor("F_Water", CVector(), 0));
  RegisterFloor(new CField_IceFloor("F_IceFloor", CVector(), -100));
  RegisterFloor(new CField_Dirt("F_Dirt", CVector(), 0));
  RegisterFloor(new CField_Dirt("F_Sand", CVector(), 1));
  RegisterFloor(new CField_Cave("F_Cave", CVector()));
  RegisterFloor(new CField_Lava("F_Lava", CVector(), 1000));
  RegisterFloor(new CField_Lava("F_ColdLava", CVector(), -200));
  RegisterFloor(new CField_Void("F_Void", CVector()));

  RegisterWall(new CField_Wall_Tree("W_Tree", CVector()));
  RegisterWall(new CField_Wall_Log("W_Log", CVector(), 0));
  RegisterWall(new CField_Wall_Log("W_Log_Burning", CVector(), 1));
  RegisterWall(new CField_Wall_Log("W_Log_Burned", CVector(), 2));
  RegisterWall(new CField_Wall_Vegetable("W_Vegetable_carrot", CVector(), 0));
  RegisterWall(new CField_Wall_Vegetable("W_Vegetable_radish", CVector(), 1));
  RegisterWall(new CField_Wall_Well("W_Well", CVector()));

  std::string direction[] = {"",     "_U",   "_D",   "_R",   "_L",  "_UR",
                             "_UD",  "_UL",  "_RL",  "_DR",  "_DL", "_URL",
                             "_UDR", "_DRL", "_UDL", "_UDRL"};
  for (int i = 0; i < 16; i++) {
    RegisterWall(
        new CField_Wall_WoodFence("W_WoodFence" + direction[i], CVector(), i));
  }

  RegisterWall(new CField_Wall_DeepWater("W_DeepWater", CVector()));

  for (int i = 0; i < 16; i++) {
    RegisterWall(new CField_Wall_Cave("W_Cave" + direction[i], CVector(), i));
  }
  RegisterWall(new CField_Wall_Rock("W_Rock", CVector()));
  RegisterWall(new CField_Decoration_Torch("W_Torch", CVector()));
  RegisterWall(new CField_Decoration_Light("W_Light", CVector()));

  std::string buf;
  for (int i = 0; i < Constant::kNumEnemySpawner; i++) {
    buf = "E" + std::to_string(i);
    RegisterWall(new CField_Wall_EnemySpawner(buf, CVector(), i));
  }
  RegisterWall(new CField_Wall_PlayerSpawner("P0", CVector()));

  RegisterWall(new CField_Void("W_Void", CVector()));
}

CField* CFieldFactory::create(int x, int y, std::string name) {
  x *= 32;
  x += 16;
  y *= 32;
  y += 16;
  //ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
  if (name[0] == 'W' || name[0] == 'E' || name[0] == 'P') {
    auto itr =
        std::find_if(wall_prototypes_.begin(), --wall_prototypes_.end(),
                     [name](std::unique_ptr<CField>& f) { return *f == name; });
    return ((*itr)->Clone(CVector(x, y)));
  } else {
    auto itr =
        std::find_if(floor_prototypes_.begin(), --floor_prototypes_.end(),
                     [name](std::unique_ptr<CField>& f) { return *f == name; });
    return ((*itr)->Clone(CVector(x, y)));
  }
}

CField* CFieldFactory::create(CVector pos, std::string name) {
  pos.x *= 32;
  pos.x += 16;
  pos.y *= 32;
  pos.y += 16;
  //ここに名前とパラメータを使ってCFieldを生成する処理をゴリゴリと書いていく
  if (name[0] == 'W' || name[0] == 'E' || name[0] == 'P') {
    auto itr =
        std::find_if(wall_prototypes_.begin(), --wall_prototypes_.end(),
                     [name](std::unique_ptr<CField>& f) { return *f == name; });
    return ((*itr)->Clone(pos));
  } else {
    auto itr =
        std::find_if(floor_prototypes_.begin(), --floor_prototypes_.end(),
                     [name](std::unique_ptr<CField>& f) { return *f == name; });
    return ((*itr)->Clone(pos));
  }
}

// category_=0:Floor, 1:Wall
std::string CFieldFactory::getKey(int* n, int category_) {
  if (category_ == 1) {
    auto itr = wall_prototypes_.begin();
    if (*n < 0) {
      *n = 0;
    }
    if (*n > wall_prototypes_.size() - 1) {
      *n = (int)wall_prototypes_.size() - 1;
    }
    for (int i = 0; i < *n; i++) {
      itr++;
    }
    return (*itr)->GetGID();
  } else {
    auto itr = floor_prototypes_.begin();
    if (*n < 0) {
      *n = 0;
    }
    if (*n > floor_prototypes_.size() - 1) {
      *n = (int)floor_prototypes_.size() - 1;
    }
    for (int i = 0; i < *n; i++) {
      itr++;
    }
    return (*itr)->GetGID();
  }
}

void CFieldFactory::Render(int category_) const {
  switch (category_) {
    case 0:
      for (const auto& p : floor_prototypes_) {
        p->Render();
      }
      break;
    case 1:
      for (const auto& p : wall_prototypes_) {
        p->Render();
      }
      break;
  }
}
