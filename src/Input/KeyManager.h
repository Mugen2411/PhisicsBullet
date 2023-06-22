#pragma once
#include "Singleton.h"
class KeyManager : public Singleton<KeyManager> {
 public:
  enum KEY_CODE { kUp, kDown, kRight, kLeft, kEnter, kCancel, kOther, kOther2 };
  KeyManager();
  ~KeyManager();

  void Update();
  int Get(int ID);
  int Get(KEY_CODE ID);

 protected:
  char buf_[256];
  int key_[256];
  int keycode_[8];
};
