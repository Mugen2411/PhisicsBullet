#pragma once

class CAnimationCounter {
 public:
  CAnimationCounter(double max, double tick)
      : current_(0.0), max_(max), tick_(tick) {}
  void Update() {
    current_ += tick_;
    if (current_ >= max_) current_ = 0.0;
  }

  double Get() const { return current_;
  }

  void Reset() { current_ = 0.0;
  }
 private:
  double current_;
  double max_;
  double tick_;
};