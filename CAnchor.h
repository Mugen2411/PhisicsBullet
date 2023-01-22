#pragma once
#include <list>
#include <random>

#include "CVector.h"
#include "Singleton.h"

class CAnchor : public Singleton<CAnchor> {
 public:
  CAnchor();

  void SetPosition(CVector newPos);
  inline void SetScrollLimit(CVector mapSize) {
    scroll_limit_ = mapSize * 32 + CVector(0, 0);
  }  //マップの大きさを整数値で
  inline CVector GetAnchoredPosition(CVector pos) {
    if (is_absolute_) return pos;
    return pos - position_;
  }
  inline CVector GetWorldPosition(CVector pos) { return pos + position_; }
  inline double GetAnchorX() {
    if (is_absolute_) return 0.0;
    if (!quake_queue_.empty()) return position_.x + diff_quake_.x;
    return position_.x;
  }
  inline double GetAnchorY() {
    if (is_absolute_) return 0.0;
    if (!quake_queue_.empty()) return position_.y + diff_quake_.y;
    return position_.y;
  }
  inline void Move(CVector diff) { SetPosition(position_ + diff); }
  inline void Quake(int duration, float power = 4.0f) {
    quake_queue_.emplace_back(QuakeData{duration, power});
  }
  void Update();

  inline void EnableAbsolute() { is_absolute_ = true; }
  inline void DisableAbsolute() { is_absolute_ = false; }

  private:
  struct QuakeData {
    int duration;
    float power;
  };

  CVector position_;
  bool is_absolute_;
  CVector scroll_limit_;
  CVector diff_quake_;

  std::list<QuakeData> quake_queue_;
  std::random_device seed_{};
  std::default_random_engine engine_;
  std::uniform_real_distribution<double> random_generator_;
};
