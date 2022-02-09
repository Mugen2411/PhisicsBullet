#include "CMapEditor.h"
#include "CImageManager.h"
#include "CAnchor.h"

void CMapEditor::CreateParts()
{
	char* f = new char[256];
	GetFileName(f, 255, true);
	field = std::make_shared<CFieldHolder>(f);
	delete[] f;
}

CMapEditor::CMapEditor(SceneManager* ScnMng): Scene_Abstract(ScnMng),input(CControllerFactory::getIns().getController())
{
	//SetMouseDispFlag(TRUE);
	CreateParts();
}

CMapEditor::~CMapEditor()
{
	//SetMouseDispFlag(FALSE);
}

void CMapEditor::Update()
{
	if (input.lock()->Up() % 5 == 1)CAnchor::getIns().Move(CVector(0, -16));
	if (input.lock()->Down() % 5 == 1)CAnchor::getIns().Move(CVector(0, 16));
	if (input.lock()->Right() % 5 == 1)CAnchor::getIns().Move(CVector(16, 0));
	if (input.lock()->Left() % 5 == 1)CAnchor::getIns().Move(CVector(-16, 0));

	if (input.lock()->A() == 1) {
		char *f = new char[256];
		GetFileName(f, 255, true);
		field = std::make_shared<CFieldHolder>(f);
		delete[] f;
	}
	if (input.lock()->B() == 1) {
		field->Save();
		MessageBox(NULL, "セーブされました", "MapEditor", MB_OK);
	}
}

void CMapEditor::Render()const
{
	//printfDx("X:%d, Y:%d\n", input.lock()->MouseX(), input.lock()->MouseY());
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("editor_cursor")->DrawRota(input.lock()->MouseX(), input.lock()->MouseY(), 0.0, 1.0, 1.0, 0);
	CAnchor::getIns().disableAbsolute();
	field->Render();
	
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
	o.lpstrFile = filename;
	o.nMaxFile = bufsize;
	o.lpstrFilter = "mapファイル(*.map)";
	o.lpstrDefExt = "map";
	o.lpstrTitle = isOpen ? "ファイルを開く" : "ファイルを保存";
	o.nFilterIndex = 1;
	o.Flags = OFN_NOCHANGEDIR;
	return GetOpenFileName(&o);
}
