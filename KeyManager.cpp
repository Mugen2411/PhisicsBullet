#include "KeyManager.h"

#include <DxLib.h>

KeyManager::KeyManager()
    : keycode_{KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_RIGHT, KEY_INPUT_LEFT,
              KEY_INPUT_Z,  KEY_INPUT_X,    KEY_INPUT_C,     KEY_INPUT_V} {
  ZeroMemory(key_, sizeof(key_));
  ZeroMemory(buf_, sizeof(buf_));
}

KeyManager::~KeyManager() {}

void KeyManager::Update() {
  GetHitKeyStateAll(buf_);
  for (int i = 0; i < 256; i++) {
    if (buf_[i]) {
      key_[i]++;
    } else
      key_[i] = 0;
  }
}

int KeyManager::Get(int ID) { return key_[ID]; }

int KeyManager::Get(KEY_CODE ID) { return key_[keycode_[ID]]; }
