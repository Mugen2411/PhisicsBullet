#include "CMapEditor.h"

void CMapEditor::CreateParts()
{
}

CMapEditor::CMapEditor(SceneManager* ScnMng): Scene_Abstract(ScnMng)
{
}

void CMapEditor::Update()
{
}

void CMapEditor::Render()const
{
	DrawCircle(320, 240, 120, 0xFF0000);
}

void CMapEditor::PartsChanged(CParts* p)
{
}
