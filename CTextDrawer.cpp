#include "CTextDrawer.h"
#include <DxLib.h>

CTextDrawer::CTextDrawer() : font_path("media/font/Nosutaru-dotMPlusH-10-Regular.ttf") {
	AddFontResourceEx(font_path.c_str(), FR_PRIVATE, NULL);
	fontArray.emplace_back(CreateFontToHandle("�m�X�^���h�b�g�iM+�j", 18, 1, DX_FONTTYPE_EDGE));
	fontArray.emplace_back(CreateFontToHandle("�m�X�^���h�b�g�iM+�j", 36, 1, DX_FONTTYPE_EDGE));
}

CTextDrawer::~CTextDrawer() {
	RemoveFontResourceEx(font_path.c_str(), FR_PRIVATE, NULL);
}

void CTextDrawer::Register(Text txt) {
	textQueue.push_back(txt);
}

void CTextDrawer::Render()const {
	for (auto& i : textQueue) {
		DrawStringToHandle(i.position.x, i.position.y, i.text.c_str(), i.mainColor, fontArray[i.fontID], i.edgeColor);
	}
}

void CTextDrawer::Clear() {
	textQueue.clear();
}