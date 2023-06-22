#include "CField_Wall_Tree.h"

CField_Wall_Tree::CField_Wall_Tree(std::string gid, CVector position_)
    : CField_Wall(gid, position_, COF().SetReflectCF(0.9)) {}

void CField_Wall_Tree::Update() {}

void CField_Wall_Tree::Render() const {
  CImageManager::GetIns()
      .Find("Field_Tree")
      ->DrawRota(position_ - CVector(0,16), 0.0, 1.0, Constant::kPriorityWall,
                 0);
}

CField* CField_Wall_Tree::Clone(CVector position_) {
  return new CField_Wall_Tree(gid_, position_);
}
