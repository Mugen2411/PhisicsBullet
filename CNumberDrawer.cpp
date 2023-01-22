#include "CNumberDrawer.h"

#include <cmath>

#include "CImageManager.h"

CNumberDrawer::CNumberDrawer() : x_num_(12) {}

void CNumberDrawer::Draw(int x, int y, double num, int type, int style,
                         int priority) const {
  int margin;
  int width;
  std::string id;
  switch (style) {
    case 0:
      id = "effect_number1";
      margin = 5;
      width = 10;
      break;
    case 1:
      id = "effect_number2";
      margin = 3;
      width = 7;
      break;
  }

  if (num < 0) return;
  if (num == 0) {
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                               x_num_ * type);
    return;
  }
  if (num < 1) {
    int l = 2;
    x -= 4 * margin;
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                               x_num_ * type);
    x += width;
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                               x_num_ * type + 10);
    x += width;
    for (int i = 0; i < l; i++) {
      num *= 10;
      CImageManager::GetIns().Find(id)->DrawRota(
          x, y, 0, 1, priority, x_num_ * type + (int)(std::fmod(num, 10.0)));
      x += width;
    }
    if (style == 2)
      CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority, 10);
    return;
  }
  int l = (int)std::log10(num) + 1;
  x += (l + 2) * margin;
  num *= 10;
  CImageManager::GetIns().Find(id)->DrawRota(
      x, y, 0, 1, priority, x_num_ * type + (int)(std::fmod(num, 10.0)));
  x -= width;
  CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                             x_num_ * type + 10);
  x -= width;
  num /= 10;
  for (int i = 0; i < l; i++) {
    CImageManager::GetIns().Find(id)->DrawRota(
        x, y, 0, 1, priority, x_num_ * type + (int)(std::fmod(num, 10.0)));
    num = std::floor(num);
    num *= 0.1;
    x -= width;
  }
  if (style == 2)
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority, 10);
}

void CNumberDrawer::Draw(int x, int y, int num, int type, int style,
                         int priority) const {
  int margin;
  int width;
  std::string id;
  switch (style) {
    case 0:
      id = "effect_number1";
      margin = 5;
      width = 10;
      break;
    case 1:
      id = "effect_number2";
      margin = 3;
      width = 7;
      break;
    case 2:
      id = "effect_number3";
      margin = 5;
      width = 10;
      break;
    case 3:
      id = "effect_number4";
      margin = 16;
      width = 16;
      break;
  }

  if (num < 0) return;
  if (num == 0) {
    x += margin;
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                               x_num_ * type);
    if (style == 2 || style == 3) {
      x -= width;
      CImageManager::GetIns().Find(id)->DrawRota(x, y, 0.0, 1.0, priority, 10);
    }
    return;
  }
  int l = (int)std::log10(num) + 1;
  x += l * margin;
  for (int i = 0; i < l; i++) {
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0, 1, priority,
                                               x_num_ * type + num % 10);
    num /= 10;
    x -= width;
  }
  if (style == 2 || style == 3)
    CImageManager::GetIns().Find(id)->DrawRota(x, y, 0.0, 1.0, priority, 10);
}
