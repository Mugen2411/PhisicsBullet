#pragma once
#include <list>

#include "CVector.h"
#include "Singleton.h"

class CEffect_Bright : public Singleton<CEffect_Bright> {
 public:
  struct BrightDesc {
    CVector position_;
    double radius;
    int power;
    BrightDesc(CVector pos, double radius, int power)
        : position_(pos), radius(radius), power(power) {}
  };

  void Register(BrightDesc b) { list_.emplace_back(b); }
  void SetBrightLevel(double l) { bright_level_ = l; }
  void Render() const;
  void Clear() { list_.clear(); }

  void SetOffScreen(int screen) { offscreen_ = screen; }

  void Activate() { active_ = true; }
  void Inactivate() { active_ = false; }

 protected:
  CEffect_Bright();

  bool active_;

  int offscreen_;
  int bright_screen_;
  int shadow_screen_;
  int bright_buffer_;
  int shadow_buffer_;
  double bright_level_;
  int bright_graph_;

  std::list<BrightDesc> list_;

  friend Singleton<CEffect_Bright>;
};