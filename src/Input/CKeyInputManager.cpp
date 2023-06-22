#include "CKeyInputManager.h"

#include "Calc/Constant.h"

int CKeyInputManager::IsChanged() { return changed_; }

int CKeyInputManager::Update() {
  int r = 0;
  for (int i = 0; i < 10; i++) {
    if (CheckHitKey(key_config_[i])) {
      pushed_frame_[i]++;
      if (kUp <= i && i <= kLeft) r = 1;
    } else
      pushed_frame_[i] = 0;
#ifdef _DEBUG
    printfDx("%d:%d\n", i, pushed_frame_[i]);
#endif
  }
  changed_ = r;

  int nx, ny;
  GetMousePoint(&nx, &ny);
  mx_ += (nx - (Constant::kScreenW / 2)) / 2;
  my_ += (ny - (Constant::kScreenH / 2)) / 2;
  if (mx_ < 0) mx_ = 0;
  if (mx_ > Constant::kScreenW) mx_ = Constant::kScreenW;
  if (my_ < 0) my_ = 0;
  if (my_ > Constant::kScreenH) my_ = Constant::kScreenH;
  if (GetWindowActiveFlag() && !is_mouse_shown_)
    SetMousePoint(Constant::kScreenW / 2, Constant::kScreenH / 2);

  int mi = GetMouseInput();
  if (mi & MOUSE_INPUT_LEFT) {
    clicked_frame_[0][1]++;
    clicked_frame_[0][0] = 0;
  } else {
    clicked_frame_[0][0]++;
    clicked_frame_[0][1] = 0;
  }
  if (mi & MOUSE_INPUT_RIGHT) {
    clicked_frame_[1][1]++;
    clicked_frame_[1][0] = 0;
  } else {
    clicked_frame_[1][0]++;
    clicked_frame_[1][1] = 0;
  }
  if (mi & MOUSE_INPUT_MIDDLE) {
    clicked_frame_[2][1]++;
    clicked_frame_[2][0] = 0;
  } else {
    clicked_frame_[2][0]++;
    clicked_frame_[2][1] = 0;
  }

  return r;
}

void CKeyInputManager::Load() {
  if (GetActiveFlag())
    SetMousePoint(Constant::kScreenW / 2, Constant::kScreenH / 2);
  SetMouseDispFlag(is_mouse_shown_);
}
