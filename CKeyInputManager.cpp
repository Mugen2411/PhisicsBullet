#include "CKeyInputManager.h"

int CKeyInputManager::update()
{
	int r = 0;
	for (int i = 0; i < 9; i++) {
		if (CheckHitKey(KeyConfig[i]) == 1) {
			pushedFrame[i]++;
			if (SK_UP <= i && i <= SK_LEFT)r = 1;
		}
		else pushedFrame[i] = 0;
	}
	return r;
}

void CKeyInputManager::load()
{
}
