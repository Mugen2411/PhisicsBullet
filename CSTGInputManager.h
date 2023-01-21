#pragma once
#include "CVector.h"

class CSTGInputManager {
 protected:
  enum STG_KEYCODE {
    NO_CONFIG = -1,
    SK_UP,
    SK_DOWN,
    SK_RIGHT,
    SK_LEFT,
    SK_A,
    SK_B,
    SK_C,
    SK_SLOW,
    SK_START,
    SK_SELECT
  };

  int pushedFrame[10];
  int mx, my;
  int clickedFrame[3][2];
  bool isMouseShown;

  struct ConfigData {
    int Up;
    int Down;
    int Right;
    int Left;
    int A;
    int B;
    int C;
    int Slow;
    int Start;
    int Select;
  } ConfDat;

 public:
  CSTGInputManager();
  virtual ~CSTGInputManager(){};

  int Up();
  int Down();
  int Right();
  int Left();
  int A();
  int B();
  int C();
  int Slow();
  int Start();
  int Select();

  int LClick(bool isPush);
  int RClick(bool isPush);
  int CClick(bool isPush);

  int MouseX();
  int MouseY();

  CVector getVector();
  int getDirection();

  float getMouseAngle(CVector p);

  virtual int isChanged() = 0;
  virtual int update() = 0;

  virtual void SetMouseVisible() = 0;
  virtual void SetMouseInvisible() = 0;
};
