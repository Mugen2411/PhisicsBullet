#include "CField_IceFloor.h"

#include <DxLib.h>

CField_IceFloor::CField_IceFloor(std::string gid, CVector position_,
                                 double temperature, int direction)
    : CField(gid, position_, CVector(32.0, 32.0),
             COF().SetFrictionCF(0.5).SetAirResCF(0.9),
             temperature, CAttribute(0.0).Ice(2.0)),
      direction_(direction),
      cnt_(0),
      kAnimDur(180) {}

void CField_IceFloor::Update() {
  cnt_++;
  if (temperature_ < 0) {
    cofs_.SetWaterResCF(0.0).SetFrictionCF(0.001);
    damage_ = CAttribute(0.0).Ice(4.0);
  } else {
    cofs_.SetWaterResCF(0.6).SetFrictionCF(0.3);
    damage_ = CAttribute(0.0).Aqua(4.0);
  }
}

void CField_IceFloor::Render() const {
  if (temperature_ < 0)
    CImageManager::GetIns()
        .Find("Field_IceFloor")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField, 0);
  else {
    CImageManager::GetIns()
        .Find("Field_IceFloor")
        ->DrawRota(position_, 0.0, 1.0, Constant::kPriorityField, 1);
    if (direction_ & 1) {
      CImageManager::GetIns()
          .Find("Field_IceFloor")
          ->DrawRota(
              position_ +
                  CVector(0.0,
                          -14.0 - sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99),
              Constant::kPI2 / 4 * 0, 1.0, Constant::kPriorityField + 1, 3);
    }
    if (direction_ & 2) {
      CImageManager::GetIns()
          .Find("Field_IceFloor")
          ->DrawRota(
              position_ +
                  CVector(14.0 + sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                          0.0),
              Constant::kPI2 / 4 * 1, 1.0, Constant::kPriorityField + 1, 3);
    }
    if (direction_ & 4) {
      CImageManager::GetIns()
          .Find("Field_IceFloor")
          ->DrawRota(
              position_ +
                  CVector(0.0,
                          14.0 + sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99),
              Constant::kPI2 / 4 * 2, 1.0, Constant::kPriorityField + 1, 3);
    }
    if (direction_ & 8) {
      CImageManager::GetIns()
          .Find("Field_IceFloor")
          ->DrawRota(
              position_ +
                  CVector(-14.0 - sin(Constant::kPI2 / kAnimDur * cnt_) * 1.99,
                          0.0),
              Constant::kPI2 / 4 * 3, 1.0, Constant::kPriorityField + 1, 3);
    }
  }
}

CField* CField_IceFloor::Clone(CVector position_) {
  return new CField_IceFloor(gid_, position_, temperature_, direction_);
}

void CField_IceFloor::Save(std::ofstream& fout) {
  auto t = gid_;
  do {
    t.pop_back();
  } while (t.back() != '_');
  t.pop_back();
  fout << t << std::endl;
}
