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

CMapEditor::CMapEditor(SceneManager* ScnMng) : Scene_Abstract(ScnMng), 
	input(CControllerFactory::getIns().getController()), currentMapchip("NULL-OBJECT"), CFF(CFieldFactory()), state(0), category(0)
{
	CAnchor::getIns().setPosition(CVector(0, 0));
	//SetMouseDispFlag(TRUE);
	CreateParts();
}

CMapEditor::~CMapEditor()
{
	//SetMouseDispFlag(FALSE);
}

void CMapEditor::Update()
{
	currentSelect = CAnchor::getIns().getWorldPosition(CVector(input.lock()->MouseX(), input.lock()->MouseY())) / 32;
	switch (state) {
	case 0:

		if (input.lock()->Up() % 5 == 1)CAnchor::getIns().Move(CVector(0, -32));
		if (input.lock()->Down() % 5 == 1)CAnchor::getIns().Move(CVector(0, 32));
		if (input.lock()->Right() % 5 == 1)CAnchor::getIns().Move(CVector(32, 0));
		if (input.lock()->Left() % 5 == 1)CAnchor::getIns().Move(CVector(-32, 0));

		if (input.lock()->A() == 1) { state = 1; return; }

		if (input.lock()->LClick(true) == 1 || input.lock()->LClick(true) > 10) {
			switch (category) {
			case 0:
				field->writefloor(CFF.create(currentSelect.x, currentSelect.y, currentMapchip), currentSelect.x, currentSelect.y);
				break;
			case 1:
				field->writewall(CFF.create(currentSelect.x, currentSelect.y, currentMapchip), currentSelect.x, currentSelect.y);
				break;
			}
			
		}

		if (input.lock()->Start() == 1) {
			char* f = new char[256];
			GetFileName(f, 255, true);
			field = std::make_shared<CFieldHolder>(f);
			delete[] f;
		}
		if (input.lock()->B() == 1) {
			field->Save();
			MessageBox(NULL, "セーブされました", "MapEditor", MB_OK);
		}
		break;
	case 1:
		if (input.lock()->LClick(true) == 1) {
			currentSelect = CAnchor::getIns().getAnchoredPosition(CVector(input.lock()->MouseX(), input.lock()->MouseY())) / 32;
			cur = (int)(currentSelect.x) + (int)(currentSelect.y) * 20;
			currentMapchip = CFF.getKey(&cur, category);
			state = 0;
			return;
		}
		if (input.lock()->RClick(true) == 1) {
			category++;
			category %= 2;
		}
		break;
	}
}

void CMapEditor::Render()const
{
	switch (state) {
	case 0:
		printfDx("Cur:%d\nPos:%d,%d\nCurentMapChip:%s\n", cur, (int)currentSelect.x, (int)currentSelect.y, currentMapchip.c_str());
		field->Render();
		break;
	case 1:
		CAnchor::getIns().enableAbsolute();
		CFF.Render(category);
		CAnchor::getIns().disableAbsolute();
		break;
	}
	CVector mousePos((int)(currentSelect.x) * 32 + 16, (int)(currentSelect.y) * 32 + 16);
	printfDx("Mouse:%lf,%lf\n", mousePos.x, mousePos.y);
	mousePos = CAnchor::getIns().getAnchoredPosition(mousePos);
	CAnchor::getIns().enableAbsolute();
	CImageManager::getIns().find("editor_cursor")->DrawRota(mousePos.x, mousePos.y, 0.0, 1.0, 1.0, 0);
	printfDx("AbsMouse:%lf,%lf\n", mousePos.x, mousePos.y);
	CAnchor::getIns().disableAbsolute();
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
