#pragma once
#include "CSTGInputManager.h"
#include <DxLib.h>

class CKeyInputManager :
    public CSTGInputManager
{
private:

    int KeyConfig[10];

public:

    CKeyInputManager():CSTGInputManager(), KeyConfig{KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_D, KEY_INPUT_A,
        KEY_INPUT_Z, KEY_INPUT_X, KEY_INPUT_C, KEY_INPUT_LSHIFT, KEY_INPUT_ESCAPE, KEY_INPUT_LCONTROL }
    {}

    int update();
    void load();
};

