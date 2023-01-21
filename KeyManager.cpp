#include "KeyManager.h"

#include <DxLib.h>

KeyManager::KeyManager()
    : keycode{KEY_INPUT_UP, KEY_INPUT_DOWN, KEY_INPUT_RIGHT, KEY_INPUT_LEFT,
              KEY_INPUT_Z,  KEY_INPUT_X,    KEY_INPUT_C,     KEY_INPUT_V} {
  ZeroMemory(key, sizeof(key));
  ZeroMemory(buf, sizeof(buf));
}

KeyManager::~KeyManager() {}

void KeyManager::update() {
  GetHitKeyStateAll(buf);
  for (int i = 0; i < 256; i++) {
    if (buf[i]) {
      key[i]++;
    } else
      key[i] = 0;
  }
}

int KeyManager::get(int ID) { return key[ID]; }

int KeyManager::Get(KEY_CODE ID) { return key[keycode[ID]]; }
