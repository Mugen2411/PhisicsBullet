#pragma once
class CNumberDrawer {
 public:
  CNumberDrawer();
  void Draw(int x, int y, double num, int type, int style,
            int priority) const;
  void Draw(int x, int y, int num, int type, int style, int priority) const;

 private:
  const int x_num_;
};
