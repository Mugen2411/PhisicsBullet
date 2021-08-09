#include "CNumberDrawer.h"
#include "CImageManager.h"
#include <cmath>

CNumberDrawer::CNumberDrawer()
{
	CImageManager::getIns().set("SystemNumber", std::make_shared<CImage>("media/graphic/system/font/num1.png", 44, 11, 4, 10, 10));
	CImageManager::getIns().set("SystemNumber2", std::make_shared<CImage>("media/graphic/system/font/num2.png", 44, 11, 4, 7, 7));
}

void CNumberDrawer::Draw(int x, int y, double num, int type, int style)const
{
	int margin = (style == 1) ? 3 : 5;
	int width = (style == 1) ? 7 : 10;
	std::string id = (style == 1) ? "SystemNumber2" : "SystemNumber";

	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 11 * type);
		return;
	}
	if (num < 1) {
		int l = 2;
		x -= 4 * margin;
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type);
		x += width;
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + 10);
		x += width;
		for (int i = 0; i < l; i++) {
			num *= 10;
			CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
			x += width;
		}
		return;
	}
	int l = std::log10(num)+1;
	x += (l + 2) * margin;
	num *= 10;
	CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
	x -= width;
	CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + 10);
	x -= width;
	num /= 10;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + (int)num % 10);
		num /= 10;
		x -= width;
	}
}

void CNumberDrawer::Draw(int x, int y, int num, int type, int style)const
{
	int margin = (style == 1) ? 3 : 5;
	int width = (style == 1) ? 7 : 10;
	std::string id = (style == 1) ? "SystemNumber2" : "SystemNumber";

	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type);
		return;
	}
	int l = std::log10(num)+1;
	x += l * margin;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, 0.5, 11 * type + num % 10);
		num /= 10;
		x -= width;
	}
}
