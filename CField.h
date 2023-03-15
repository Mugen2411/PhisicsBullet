#pragma once
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "CAnchor.h"
#include "CAttribute.h"
#include "CFieldParent.h"
#include "CImage.h"
#include "CImageManager.h"
#include "CMover.h"
#include "CVector.h"

class CMover_ShotBase;
class CMover_BulletBase;

class CField {
 public:
  CField(std::string gid, CVector position_, CVector size, COF cofs,
         double temperature, CAttribute damage = CAttribute(0.0),
         bool is_wall_ = false);
  virtual ~CField(){};

  inline bool operator==(std::string gid) const { return (gid == gid_); }
  inline bool IsInScreen() {
    const int size_ = 32;
    auto p = CAnchor::GetIns().GetAnchoredPosition(position_);
    if (p.x_ + size_ > 0 && p.x_ - size_ < Constant::kScreenW && p.y_ + size_ > 0 &&
        p.y_ - size_ < Constant::kScreenH)
      return true;
    return false;
  }
  inline std::string GetGID() { return gid_; }
  inline CAttribute GetDamage() { return damage_; }
  inline CVector GetPosition() { return position_; }
  inline CVector GetSize() { return size_; }

  virtual void SetFrictionForce(CMover* m);
  void AttributeEffect(CMover* m){};
  void AttributeEffect(CMover_ShotBase* m);
  void AttributeEffect(CMover_BulletBase* m);

  virtual void AttributeReaction(CAttribute) {}

  inline void Move(CVector p) { position_ = p; }
  virtual CField* Clone(CVector position_) = 0;

  virtual bool Hit(CMover* m) {
    return false;
  }  //近くに物体があるときに呼ばれる、何もしたくなければしなくてもいい
  virtual void Update();
  virtual void Render() const;

  virtual void Save(std::ofstream& fout);

  bool is_wall_;

 protected:
  CVector position_;
  CVector size_;
  COF cofs_;
  double temperature_;
  CAttribute damage_;

  std::string gid_;

 private:
  int damage_interval_;

  friend CFieldHolder;
};
