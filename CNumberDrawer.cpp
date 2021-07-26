#include "CNumberDrawer.h"
#include "CImageManager.h"
#include <cmath>

CNumberDrawer::CNumberDrawer()
{
	CImageManager::getIns().set("SystemNumber", std::make_shared<CImage>("media/graphic/system/font/num1.png", 40, 10, 4, 10, 10));
}

const void CNumberDrawer::Draw(int x, int y, int num, int type)
{
	if (num == 0) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 10 * type);
		return;
	}
	int l = std::ceil(std::log10(num));
	x += l * 5;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 10 * type + num % 10);
		num /= 10;
		x -= 10;
	}
}
