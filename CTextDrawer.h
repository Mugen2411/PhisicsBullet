#pragma once
#include "Singleton.h"
#include <string>
#include "CVector.h"
#include <list>
#include <vector>

class CTextDrawer :public Singleton<CTextDrawer>{
public:
	struct Text {
		std::string text;
		CVector position;
		int mainColor;
		int edgeColor;
		int fontID;

		Text(std::string text, CVector position, int mainColor , int edgeColor, int fontID):
		text(text) ,position(position), mainColor(mainColor), edgeColor(edgeColor), fontID(fontID) {
		}
		Text() {}
	};
	void Register(Text txt);
	void RegisterForCostumeDetail(Text txt);
	void Render()const;
	void Clear();

private:
	std::vector<int> fontArray;
	std::list<Text> textQueue;
	std::list<Text> costumeDetailQueue;

	std::string font_path;

	CTextDrawer();
	~CTextDrawer();

	friend class Singleton<CTextDrawer>;
};
