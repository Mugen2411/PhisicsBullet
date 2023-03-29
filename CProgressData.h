#pragma once
#include <DxLib.h>

#include <algorithm>
#include <list>
#include <random>
#include <string>

#include "Singleton.h"

class CProgressData : public Singleton<CProgressData> {
 public:
  void Save();
  void Load();

  void SetCurrentStage(int stage) {  //���ɓ���X�e�[�W(Mediator����ݒ�)
    if (!is_endless_)
      current_stage_ = (std::min)(stage, max_stage_);
    else
      current_stage_ = stage;
  }
  void NextCurrentStage() {  //���ɓ���X�e�[�W(Mediator����ݒ�)
    if (!is_endless_)
      current_stage_ = (std::min)(++current_stage_, max_stage_);
    else
      current_stage_ = ++current_stage_;
  }
  int GetLastStage()  //���܂łɐi�񂾍ő�̃X�e�[�W
  {
    return data_.last_stage;
  }
  int GetEndlessLast() { return data_.endless_last; }

  int GetCurrentStage()  //���ɓ���X�e�[�W(Mediator����Q��)
  {
    return current_stage_;
  }
  int GetMaxStage() { return max_stage_; }

  std::string GetMapFilepath() {
    int cur = current_stage_;
    if (is_endless_) {
      if (random_stage_.empty()) {
        do {
          ShuffleStage();
        } while (random_stage_.back() == before_stage_);
      }
      cur = random_stage_.back();
      random_stage_.pop_back();
      before_stage_ = cur;
    }
    return std::string("media/map/") + std::to_string(cur % max_stage_) +
           std::string("/") + std::to_string(cur % max_stage_) +
           std::string(".map");
  }

  int GetPlayerLevel() { return data_.player_level_; }

  double GetMoney() { return data_.money; }

  void SetWindowX2(int v) {  // 0:�g�喳�� 1:2�{�g��
    if (v)
      data_.is_option_flags |= (v & 1);
    else
      data_.is_option_flags &= (v & 1);
  }

  int GetWindowX2() { return data_.is_option_flags & 1; }

  void SetFMorPCM(int v) {  // 0:PCM 1:FM
    if (v)
      data_.is_option_flags |= ((v & 1) << 1);
    else
      data_.is_option_flags &= ((v & 1) << 1);
  }

  int GetFMorPCM() { return (data_.is_option_flags >> 1) & 1; }

  void SetEndless(bool flag) { is_endless_ = flag; }

  bool GetEndless() { return is_endless_; }

  void Upgrade(double money) {
    data_.money -= money;
    data_.player_level_++;
  }

  void Degrade() { data_.player_level_--; }

  void Win(double money);     //���������̊l������
  void Lose(double money);    //���������̊l������
  void Retire(double money);  //���߂����̊l������

  double GetEarnedMoney() { return earned_money_; }
  int GetStageMoney() { return stage_money_; }

 private:
  CProgressData();

  int current_stage_;
  int max_stage_;
  double earned_money_;
  int stage_money_;
  int before_stage_;

  std::vector<int> random_stage_;
  std::random_device dev_;
  std::mt19937 eng_;

  bool is_endless_;

  struct ProgressData {
    int last_stage;  //
    double money;
    int player_level_;
    int is_option_flags;  //����1bit:�g�嗦(0=x1_,1=x2_),2bit:����(0=PCM, 1=FM)
    int endless_last;  // 10��������Ǝn�߂�ׂ��X�e�[�W�ɂȂ�
  } data_;

  void ShuffleStage() {
    random_stage_.clear();
    for (int i = 0; i < max_stage_; i++) {
      random_stage_.push_back(i);
    }
    std::shuffle(random_stage_.begin(), random_stage_.end(), eng_);
  }

  friend class Singleton<CProgressData>;
};