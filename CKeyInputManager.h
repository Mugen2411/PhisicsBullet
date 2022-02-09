#pragma once
#include "CSTGInputManager.h"
#include <DxLib.h>

class CKeyInputManager :
    public CSTGInputManager
{
private:

    int KeyConfig[10];
    int changed;

public:

    CKeyInputManager():CSTGInputManager(), KeyConfig{KEY_INPUT_W, KEY_INPUT_S, KEY_INPUT_D, KEY_INPUT_A,
        KEY_INPUT_Z, KEY_INPUT_SPACE, KEY_INPUT_X, KEY_INPUT_C, KEY_INPUT_ESCAPE, KEY_INPUT_LCONTROL }, changed(0)
    {
        load();
    }
    int isChanged();
    int update();
    void load();
};

