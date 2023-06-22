#pragma once
#include <DxLib.h>

#include "CSTGInputManager.h"

class CKeyInputManager final : public CSTGInputManager {
 public:
  CKeyInputManager()
      : CSTGInputManager(),
        key_config_{KEY_INPUT_W,      KEY_INPUT_S,     KEY_INPUT_D, KEY_INPUT_A,
                  KEY_INPUT_E,      KEY_INPUT_SPACE, KEY_INPUT_X, KEY_INPUT_C,
                  KEY_INPUT_ESCAPE, KEY_INPUT_SPACE},
        changed_(0) {
    Load();
  }
  int IsChanged();
  int Update();
  void Load();

  void SetMouseVisible() {
    is_mouse_shown_ = true;
    SetMouseDispFlag(is_mouse_shown_);
  }

  void SetMouseInvisible() {
    is_mouse_shown_ = false;
    SetMouseDispFlag(is_mouse_shown_);
  }

  private:
  int key_config_[10];
  int changed_;
};
