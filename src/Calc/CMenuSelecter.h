#pragma once

//メニューにおける選択を簡単にする
class CMenuSelector {
 private:
  int cur_;
  int max_;

 public:
  //最大値と初期位置
  CMenuSelector(int context_max, int current)
      : max_(context_max), cur_(current) {
    if (this->cur_ > max_) this->cur_ = max_;
  }
  // 1項目前へ
  void Prev();
  // 1項目後へ
  void Next();
  //現在の位置を取得(0～最大値)
  int Get() const;
};
