#include "CTextDrawer.h"
#include <DxLib.h>

CTextDrawer::CTextDrawer() : font_path("media/font/Nosutaru-dotMPlusH-10-Regular.ttf"), priority(0) {
	AddFontResourceEx(font_path.c_str(), FR_PRIVATE, NULL);
	fontArray.emplace_back(CreateFontToHandle("ノスタルドット（M+）", 12, 1, DX_FONTTYPE_EDGE));
	fontArray.emplace_back(CreateFontToHandle("ノスタルドット（M+）", 36, 1, DX_FONTTYPE_EDGE));
	fontArray.emplace_back(CreateFontToHandle("ノスタルドット（M+）", 60, 1, DX_FONTTYPE_EDGE));
}

CTextDrawer::~CTextDrawer() {
	RemoveFontResourceEx(font_path.c_str(), FR_PRIVATE, NULL);
}

void CTextDrawer::Register(Text txt) {
	if (priority != 0)return;
	textQueue.push_back(txt);
}

void CTextDrawer::RegisterForCostumeDetail(Text txt)
{
	costumeDetailQueue.push_back(txt);
}

void CTextDrawer::Render()const {
	for (auto& i : textQueue) {
		DrawStringToHandle(i.position.x, i.position.y, i.text.c_str(), i.mainColor, fontArray[i.fontID], i.edgeColor);
	}
	for (auto& i : costumeDetailQueue) {
		DrawFormatStringToHandle(i.position.x, i.position.y, i.mainColor, fontArray[i.fontID], i.text.c_str());
	}
}

void CTextDrawer::Clear() {
	textQueue.clear();
	costumeDetailQueue.clear();
}