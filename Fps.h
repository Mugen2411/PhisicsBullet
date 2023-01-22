#include <DxLib.h>
#include <math.h>

class Fps {
  int start_time_;             //測定開始時刻
  int count_;                 //カウンタ
  float fps_;                 // fps_
  static const int cnt_to_sample = 60;    //平均を取るサンプル数
  static const int ideal_fps_ = 60;  //設定したFPS

 public:
  Fps() {
    start_time_ = 0;
    count_ = 0;
    fps_ = 0;
  }

  bool Update() {
    if (count_ == 0) {  // 1フレーム目なら時刻を記憶
      start_time_ = GetNowCount();
    }
    if (count_ == cnt_to_sample) {  // 60フレーム目なら平均を計算する
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
    int tookTime = GetNowCount() - start_time_;      //かかった時間
    int waitTime = count_ * 1000 / ideal_fps_ - tookTime;  //待つべき時間
    if (waitTime > 0) {
      Sleep(waitTime);  //待機
    }
  }
};