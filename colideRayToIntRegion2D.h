#pragma once
#include <vector>

struct floatCord {
  float x, y;
};

struct intCord {
  int x, y;
};

template <class F2, class I2>
bool collideRayToIntRegion2D(const F2 &sp, const F2 &ep,
                             std::vector<std::vector<I2> > &out) {
  // 初期位置が最初の衝突
  std::vector<I2> res;
  I2 initC;
  initC.x = (int)floorf(sp.x);
  initC.y = (int)floorf(sp.y);
  res.push_back(initC);
  out.push_back(res);

  // レイベクトル算出
  F2 v = ep;
  v.x -= sp.x;
  v.y -= sp.y;

  F2 s = sp;

  // レイの方向ベクトルVの成分の符号をプラス化
  int signX = 1, signY = 1;
  int adjX = 0, adjY = 0;

  if (v.x < 0.0f) {
    s.x *= -1.0f;
    v.x *= -1;
    signX = -1;
    adjX = 1;
  }
  if (v.y < 0.0f) {
    s.y *= -1.0f;
    v.y *= -1;
    signY = -1;
    adjY = 1;
  }

  // 始点を含む領域が初期領域
  I2 c;
  c.x = signX * (initC.x + adjX);
  c.y = signY * (initC.y + adjY);

  if (v.x == 0.0f && v.y == 0.0f) return true;  // レイが飛んでいないので終了

  // 衝突探索
  while (1) {
    std::vector<I2> res;
    float ax = v.x != 0.0f ? (c.x + 1 - s.x) / v.x : FLT_MAX;
    float ay = v.y != 0.0f ? (c.y + 1 - s.y) / v.y : FLT_MAX;

    if (ax > 1.0f && ay > 1.0f) break;  // レイを越えたのでおしまい

    if (ax < ay) {
      c.x += 1;  // X-Side
    } else if (ay < ax) {
      c.y += 1;  // Y-Side
    } else {
      c.x += 1;
      c.y += 1;  // 角
    }

    I2 newC;
    newC.x = signX * (c.x + adjX);
    newC.y = signY * (c.y + adjY);
    res.push_back(newC);

    if (ax == ay) {
      // 角に隣接する領域も衝突
      I2 newC0, newC1;
      newC0.x = signX * (c.x + adjX);
      newC0.y = signY * (c.y - 1 + adjY);
      newC1.x = signX * (c.x - 1 + adjX);
      newC1.y = signY * (c.y + adjY);
      res.push_back(newC0);
      res.push_back(newC1);
    }

    out.push_back(res);
  }

  return true;
}