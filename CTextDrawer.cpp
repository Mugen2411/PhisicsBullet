#include "CTextDrawer.h"

#include <DxLib.h>

CTextDrawer::CTextDrawer()
    : font_path_("media/font/Nosutaru-dotMPlusH-10-Regular.ttf"), priority_(0) {
  AddFontResourceEx(font_path_.c_str(), FR_PRIVATE, NULL);
  font_array_.emplace_back(
      CreateFontToHandle("ノスタルドット（M+）", 12, 1, DX_FONTTYPE_EDGE));
  font_array_.emplace_back(
      CreateFontToHandle("ノスタルドット（M+）", 36, 1, DX_FONTTYPE_EDGE));
  font_array_.emplace_back(
      CreateFontToHandle("ノスタルドット（M+）", 60, 1, DX_FONTTYPE_EDGE));
}

CTextDrawer::~CTextDrawer() {
  RemoveFontResourceEx(font_path_.c_str(), FR_PRIVATE, NULL);
}

void CTextDrawer::Register(Text txt) {
  if (priority_ != 0) return;
  text_queue_.push_back(txt);
}

void CTextDrawer::RegisterForCostumeDetail(Text txt) {
  costume_detail_queue_.push_back(txt);
}

void CTextDrawer::Render() const {
  for (auto& i : text_queue_) {
    DrawStringToHandle((int)i.position_.x_, (int)i.position_.y_, i.text_.c_str(), i.main_color_,
                       font_array_[i.fontID_], i.edge_color_);
  }
  for (auto& i : costume_detail_queue_) {
    DrawFormatStringToHandle((int)i.position_.x_, (int)i.position_.y_, i.main_color_,
                             font_array_[i.fontID_], i.text_.c_str());
  }
}

void CTextDrawer::Clear() {
  text_queue_.clear();
  costume_detail_queue_.clear();
}