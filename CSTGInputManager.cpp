#include "CSTGInputManager.h"

CSTGInputManager::CSTGInputManager()
    : pushedFrame{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      ConfDat{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      clickedFrame{{0, 0}, {0, 0}, {0, 0}},
      isMouseShown(true),
      mx(320),
      my(240) {}

int CSTGInputManager::Up() { return pushedFrame[SK_UP]; }

int CSTGInputManager::Down() { return pushedFrame[SK_DOWN]; }

int CSTGInputManager::Right() { return pushedFrame[SK_RIGHT]; }

int CSTGInputManager::Left() { return pushedFrame[SK_LEFT]; }

int CSTGInputManager::A() { return pushedFrame[SK_A]; }

int CSTGInputManager::B() { return pushedFrame[SK_B]; }

int CSTGInputManager::C() { return pushedFrame[SK_C]; }

int CSTGInputManager::Slow() { return pushedFrame[SK_SLOW]; }

int CSTGInputManager::Start() { return pushedFrame[SK_START]; }

int CSTGInputManager::Select() { return pushedFrame[SK_SELECT]; }

int CSTGInputManager::LClick(bool isPush) { return clickedFrame[0][isPush]; }

int CSTGInputManager::RClick(bool isPush) { return clickedFrame[1][isPush]; }

int CSTGInputManager::CClick(bool isPush) { return clickedFrame[2][isPush]; }

int CSTGInputManager::MouseX() { return mx; }

int CSTGInputManager::MouseY() { return my; }

CVector CSTGInputManager::getVector() {
  CVector tmp(0.0, 0.0);
  if (pushedFrame[SK_UP] != 0) tmp -= CVector(0.0, 1.0);
  if (pushedFrame[SK_DOWN] != 0) tmp += CVector(0.0, 1.0);
  if (pushedFrame[SK_RIGHT] != 0) tmp += CVector(1.0, 0.0);
  if (pushedFrame[SK_LEFT] != 0) tmp -= CVector(1.0, 0.0);
  return tmp.getNorm();
}

int CSTGInputManager::getDirection() {
  if (pushedFrame[SK_UP] > 0) {
    if (pushedFrame[SK_RIGHT] > pushedFrame[SK_UP])
      return SK_RIGHT;
    else
      return SK_UP;
    if (pushedFrame[SK_LEFT] > pushedFrame[SK_UP])
      return SK_LEFT;
    else
      return SK_UP;
  }
  if (pushedFrame[SK_DOWN] > 0) {
    if (pushedFrame[SK_RIGHT] > pushedFrame[SK_DOWN])
      return SK_RIGHT;
    else
      return SK_DOWN;
    if (pushedFrame[SK_LEFT] > pushedFrame[SK_DOWN])
      return SK_LEFT;
    else
      return SK_DOWN;
  }
  if (pushedFrame[SK_RIGHT] > 0) {
    if (pushedFrame[SK_UP] > pushedFrame[SK_RIGHT])
      return SK_UP;
    else
      return SK_RIGHT;
    if (pushedFrame[SK_DOWN] > pushedFrame[SK_RIGHT])
      return SK_DOWN;
    else
      return SK_RIGHT;
  }
  if (pushedFrame[SK_LEFT] > 0) {
    if (pushedFrame[SK_UP] > pushedFrame[SK_LEFT])
      return SK_UP;
    else
      return SK_LEFT;
    if (pushedFrame[SK_DOWN] > pushedFrame[SK_LEFT])
      return SK_DOWN;
    else
      return SK_LEFT;
  }
  return NO_CONFIG;
}

float CSTGInputManager::getMouseAngle(CVector p) {
  return (float)atan2(my - p.y, mx - p.x);
}
