#include <DxLib.h>
#include <math.h>

class Fps {
  int start_time_;             //����J�n����
  int count_;                 //�J�E���^
  float fps_;                 // fps_
  static const int cnt_to_sample = 60;    //���ς����T���v����
  static const int ideal_fps_ = 60;  //�ݒ肵��FPS

 public:
  Fps() {
    start_time_ = 0;
    count_ = 0;
    fps_ = 0;
  }

  bool Update() {
    if (count_ == 0) {  // 1�t���[���ڂȂ玞�����L��
      start_time_ = GetNowCount();
    }
    if (count_ == cnt_to_sample) {  // 60�t���[���ڂȂ畽�ς��v�Z����
      int t = GetNowCount();
      fps_ = 1000.f / ((t - start_time_) / (float)cnt_to_sample);
      count_ = 0;
      start_time_ = t;
    }
    count_++;
    return true;
  }

  void Draw() {
    DrawFormatString(0, 480 - 16, GetColor(255, 255, 255), "%.1f", fps_);
  }

  void Wait() {
    int tookTime = GetNowCount() - start_time_;      //������������
    int waitTime = count_ * 1000 / ideal_fps_ - tookTime;  //�҂ׂ�����
    if (waitTime > 0) {
      Sleep(waitTime);  //�ҋ@
    }
  }
};