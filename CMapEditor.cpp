#include "CMapEditor.h"

void CMapEditor::CreateParts()
{
}

CMapEditor::CMapEditor(SceneManager* ScnMng): Scene_Abstract(ScnMng),input(CControllerFactory::getIns().getController())
{
}

void CMapEditor::Update()
{
	if (input.lock()->A() == 1) {
		char *f = new char[256];
		GetFileName(f, 255, true);
		MessageBox(NULL, f, "ファイルが開かれました", MB_OK);
		delete[] f;
	}
	if (input.lock()->B() == 1) {
		char* f = new char[256];
		GetFileName(f, 255, false);
		MessageBox(NULL, f, "ファイルがセーブされました", MB_OK);
		delete[] f;
	}
}

void CMapEditor::Render()const
{
	DrawCircle(320, 240, 120, 0xFF0000);
}

void CMapEditor::PartsChanged(CParts* p)
{
}

int GetFileName(char* filename, int bufsize, bool isOpen)
{
	filename[0] = '\0';
	OPENFILENAME o;
	ZeroMemory(&o, sizeof(OPENFILENAME));
	o.lStructSize = sizeof(OPENFILENAME);
	o.hwndOwner = GetMainWindowHandle();
	o.lpstrInitialDir = "media/map";
	o.lpstrFile = filename;
	o.nMaxFile = bufsize;
	o.lpstrFilter = "mapファイル(*.map)";
	o.lpstrDefExt = "map";
	o.lpstrTitle = isOpen ? "ファイルを開く" : "ファイルを保存";
	o.nFilterIndex = 1;
	return GetOpenFileName(&o);
}
