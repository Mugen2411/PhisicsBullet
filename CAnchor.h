#pragma once
#include <list>
#include <random>

#include "CVector.h"
#include "Singleton.h"

class CAnchor : public Singleton<CAnchor> {
 private:
  CVector position;
  bool isAbsolute;
  CVector ScrollLimit;
  CVector diff_quake;

  struct quakeData {
    int duration;
    float power;
  };

  std::list<quakeData> quakeQueue;
  std::random_device seed{};
  std::default_random_engine engine;
  std::uniform_real_distribution<double> randomGenerator;

 public:
  CAnchor();

  void setPosition(CVector newPos);
  inline void setScrollLimit(CVector mapSize) {
    ScrollLimit = mapSize * 32 + CVector(0, 0);
  }  //マップの大きさを整数値で
  inline CVector getAnchoredPosition(CVector pos) {
    if (isAbsolute) return pos;
    return pos - position;
  }
  inline CVector getWorldPosition(CVector pos) { return pos + position; }
  inline double getAnchorX() {
    if (isAbsolute) return 0.0;
    if (!quakeQueue.empty()) return position.x + diff_quake.x;
    return position.x;
  }
  inline double getAnchorY() {
    if (isAbsolute) return 0.0;
    if (!quakeQueue.empty()) return position.y + diff_quake.y;
    return position.y;
  }
  inline void Move(CVector diff) { setPosition(position + diff); }
  inline void Quake(int duration, float power = 4.0f) {
    quakeQueue.emplace_back(quakeData{duration, power});
  }
  void Update();

  inline void enableAbsolute() { isAbsolute = true; }
  inline void disableAbsolute() { isAbsolute = false; }
};
