#include "CNumberDrawer.h"
#include "CImageManager.h"
#include <cmath>

CNumberDrawer::CNumberDrawer()
{
}

void CNumberDrawer::Draw(int x, int y, double num, int type, int style)const
{
	int margin;
	int width;
	std::string id;
	double priority;
	switch (style) {
	case 0:
		id = "effect_number1";
		margin = 5;
		width = 10;
		priority = 0.6;
		break;
	case 1:
		id = "effect_number2";
		margin = 3;
		width = 7;
		priority = 0.5;
		break;
	}

	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type);
		return;
	}
	if (num < 1) {
		int l = 2;
		x -= 4 * margin;
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type);
		x += width;
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + 10);
		x += width;
		for (int i = 0; i < l; i++) {
			num *= 10;
			CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + (int)num % 10);
			x += width;
		}
		if (style == 2)CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 10);
		return;
	}
	int l = std::log10(num)+1;
	x += (l + 2) * margin;
	num *= 10;
	CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + (int)num % 10);
	x -= width;
	CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + 10);
	x -= width;
	num /= 10;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + (int)num % 10);
		num /= 10;
		x -= width;
	}
	if (style == 2)CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 10);
}

void CNumberDrawer::Draw(int x, int y, int num, int type, int style)const
{
	int margin;
	int width;
	std::string id;
	double priority;
	switch (style) {
	case 0:
		id = "effect_number1";
		margin = 5;
		width = 10;
		priority = 0.6;
		break;
	case 1:
		id = "effect_number2";
		margin = 3;
		width = 7;
		priority = 0.5;
		break;
	}

	if (num < 0)return;
	if (num == 0) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type);
		return;
	}
	int l = std::log10(num)+1;
	x += l * margin;
	for (int i = 0; i < l; i++) {
		CImageManager::getIns().find(id)->DrawRota(x, y, 0, 1, priority, 11 * type + num % 10);
		num /= 10;
		x -= width;
	}
}
