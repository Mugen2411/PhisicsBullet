#pragma once

//���j���[�ɂ�����I�����ȒP�ɂ���
class CMenuSelector {
 private:
  int cur_;
  int max_;

 public:
  //�ő�l�Ə����ʒu
  CMenuSelector(int context_max, int current)
      : max_(context_max), cur_(current) {
    if (this->cur_ > max_) this->cur_ = max_;
  }
  // 1���ڑO��
  void Prev();
  // 1���ڌ��
  void Next();
  //���݂̈ʒu���擾(0�`�ő�l)
  int Get() const;
};
