#include "CNumberDrawer.h"
#include "CImageManager.h"
#include <cmath>

CNumberDrawer::CNumberDrawer()
{
	CImageManager::getIns().set("SystemNumber", std::make_shared<CImage>("media/graphic/system/font/num1.png", 44, 11, 4, 10, 10));
}

void CNumberDrawer::Draw(int x, int y, double num, int type)const
{
	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 11 * type);
		return;
	}
	if (num < 1) {
		int l = 2;
		x -= 4 * 5;
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type);
		x += 10;
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + 10);
		x += 10;
		for (int i = 0; i < l; i++) {
			num *= 10;
			CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
			x += 10;
		}
		return;
	}
	int l = std::ceil(std::log10(num));
	x += (l+2) * 5;
	num *= 10;
	CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
	x -= 10;
	CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + 10);
	x -= 10;
	num /= 10;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
		num /= 10;
		x -= 10;
	}
}

void CNumberDrawer::Draw(int x, int y, int num, int type)const
{
	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type);
		return;
	}
	int l = std::ceil(std::log10(num));
	x += l * 5;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find("SystemNumber")->DrawRota(x, y, 0, 1, 0.5, 11 * type + num % 10);
		num /= 10;
		x -= 10;
	}
}
