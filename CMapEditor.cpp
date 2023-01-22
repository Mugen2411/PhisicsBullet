#include "CMapEditor.h"

#include "CAnchor.h"
#include "CImageManager.h"

void CMapEditor::CreateParts() {
  input_.lock()->SetMouseVisible();
  char* f = new char[256];
  GetFileName(f, 255, true);
  field_ = std::make_shared<CFieldHolder>(f);
  delete[] f;
  input_.lock()->SetMouseInvisible();
}

CMapEditor::CMapEditor(SceneManager* ScnMng)
    : Scene_Abstract(ScnMng),
      input_(CControllerFactory::GetIns().GetController()),
      current_mapchip_("NULL-OBJECT"),
      field_factory_(CFieldFactory()),
      state_(0),
      category_(0) {
  CAnchor::GetIns().SetPosition(CVector(0, 0));
  CreateParts();
}

CMapEditor::~CMapEditor() {
  // SetMouseDispFlag(FALSE);
}

void CMapEditor::Update() {
  current_select_ = CAnchor::GetIns().GetWorldPosition(
                      CVector(input_.lock()->MouseX(), input_.lock()->MouseY())) /
                  32;
  switch (state_) {
    case 0:

      if (input_.lock()->Up() % 5 == 1) CAnchor::GetIns().Move(CVector(0, -32));
      if (input_.lock()->Down() % 5 == 1) CAnchor::GetIns().Move(CVector(0, 32));
      if (input_.lock()->Right() % 5 == 1)
        CAnchor::GetIns().Move(CVector(32, 0));
      if (input_.lock()->Left() % 5 == 1)
        CAnchor::GetIns().Move(CVector(-32, 0));

      if (input_.lock()->A() == 1) {
        state_ = 1;
        return;
      }

      if (input_.lock()->LClick(true) == 1 || input_.lock()->LClick(true) > 10) {
        switch (category_) {
          case 0:
            field_->WriteFloor(
                field_factory_.create(current_select_, current_mapchip_),
                current_select_);
            break;
          case 1:
            field_->WriteWall(
                field_factory_.create(current_select_, current_mapchip_),
                current_select_);
            break;
        }
      }

      if (input_.lock()->Start() == 1) {
        input_.lock()->SetMouseVisible();
        char* f = new char[256];
        GetFileName(f, 255, true);
        field_ = std::make_shared<CFieldHolder>(f);
        delete[] f;
        input_.lock()->SetMouseInvisible();
      }
      if (input_.lock()->B() == 1) {
        input_.lock()->SetMouseVisible();
        field_->Save();
        MessageBox(NULL, "セーブされました", "MapEditor", MB_OK);
        input_.lock()->SetMouseInvisible();
      }
      break;
    case 1:
      if (input_.lock()->Start() == 1) {
        scene_manager_->ChangeScene(Constant::SceneID::kSceneTitle, true);
        return;
      }
      if (input_.lock()->LClick(true) == 1) {
        current_select_ =
            CVector(input_.lock()->MouseX(), input_.lock()->MouseY()) / 32;
        cur_ = (int)(current_select_.x) + (int)(current_select_.y) * 20;
        current_mapchip_ = field_factory_.getKey(&cur_, category_);
        state_ = 0;
        return;
      }
      if (input_.lock()->RClick(true) == 1) {
        category_++;
        category_ %= 2;
      }
      break;
  }
}

void CMapEditor::Render() const {
  switch (state_) {
    case 0:
      printfDx("Cur:%d\nPos:%d,%d\nCurentMapChip:%s\n", cur_,
               (int)current_select_.x, (int)current_select_.y,
               current_mapchip_.c_str());
      field_->Render();
      break;
    case 1:
      CAnchor::GetIns().EnableAbsolute();
      field_factory_.Render(category_);
      CAnchor::GetIns().DisableAbsolute();
      break;
  }
  CVector mousePos((int)(current_select_.x) * 32 + 16,
                   (int)(current_select_.y) * 32 + 16);
  printfDx("Mouse:%lf,%lf\n", mousePos.x, mousePos.y);
  mousePos = CAnchor::GetIns().GetAnchoredPosition(mousePos);
  CAnchor::GetIns().EnableAbsolute();
  CImageManager::GetIns()
      .Find("editor_cursor")
      ->DrawRota(mousePos, 0.0f, 1.0f, 100, 0);
  printfDx("AbsMouse:%lf,%lf\n", mousePos.x, mousePos.y);
  CAnchor::GetIns().DisableAbsolute();
}

void CMapEditor::PartsChanged(CParts* p) {}

int GetFileName(char* filename, int bufsize, bool isOpen) {
  filename[0] = '\0';
  OPENFILENAME o;
  ZeroMemory(&o, sizeof(OPENFILENAME));
  o.lStructSize = sizeof(OPENFILENAME);
  o.hwndOwner = GetMainWindowHandle();
  o.lpstrFile = filename;
  o.nMaxFile = bufsize;
  // o.lpstrFilter = "mapファイル(*.map)";
  // o.lpstrDefExt = "map\0";
  o.lpstrTitle = isOpen ? "ファイルを開く" : "ファイルを保存";
  o.nFilterIndex = 1;
  o.Flags = OFN_NOCHANGEDIR;
  return GetOpenFileName(&o);
}
