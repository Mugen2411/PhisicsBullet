#include "CImage.h"

#include <DxLib.h>

#include <algorithm>

#include "CAnchor.h"
#include "CDrawCircleGauge.h"
#include "CDrawExtendWithBlend.h"
#include "CDrawGraphFReserve.h"
#include "CDrawGraphReserve.h"
#include "CDrawModiGraphReserve.h"
#include "CDrawRectGraphWithBlendReserve.h"
#include "CDrawRotaGraphFReserve.h"
#include "CDrawRotaGraphFwithBlendReserve.h"
#include "CDrawRotaGraphReserve.h"
#include "CRenderReserveList.h"

CImage::CImage(std::string path, int width, int height)
    : graphic_handle_(0),
      filepath_(path),
      array_size_(1),
      x_num_(1),
      y_num_(1),
      width_(width),
      height_(height) {}

CImage::CImage(std::string path, int AllNum, int Xnum, int Ynum, int w, int h)
    : graphic_handle_(0),
      filepath_(path),
      array_size_(AllNum),
      x_num_(Xnum),
      y_num_(Ynum),
      width_(w),
      height_(h) {}

CImage::~CImage() { Release(); }

void CImage::Release() {
  std::for_each(graphic_handle_.begin(), graphic_handle_.end(), [](int v) { DeleteGraph(v); });
  graphic_handle_.clear();
}

void CImage::Draw(int x1, int y1, int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawGraphReserve(
      graphic_handle_[num], x1 - (int)CAnchor::GetIns().GetAnchorX(),
      y1 - (int)CAnchor::GetIns().GetAnchorY(), priority, width_, height_));
}

void CImage::Draw(double x1, double y1, int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawGraphFReserve(
      graphic_handle_[num], x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), priority, width_, height_));
}

void CImage::Draw(CVector pos, int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawGraphReserve(
      graphic_handle_[num], (int)pos.x_ - (int)CAnchor::GetIns().GetAnchorX(),
      (int)pos.y_ - (int)CAnchor::GetIns().GetAnchorY(), priority, width_, height_));
}

void CImage::DrawRota(int x1, int y1, float angle, float extend, int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawRotaGraphReserve(
      graphic_handle_[num], priority, x1 - (int)CAnchor::GetIns().GetAnchorX(),
      y1 - (int)CAnchor::GetIns().GetAnchorY(), angle, extend, width_, height_));
}

void CImage::DrawRota(CVector pos, float angle, float extend, int priority,
                      unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawRotaGraphReserve(
      graphic_handle_[num], priority, (int)pos.x_ - (int)CAnchor::GetIns().GetAnchorX(),
      (int)pos.y_ - (int)CAnchor::GetIns().GetAnchorY(), angle, extend, width_,
      height_));
}

void CImage::DrawRotaF(double x1, double y1, float angle, float extend,
                       int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawRotaGraphFReserve(
      graphic_handle_[num], priority, x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), angle, extend, width_, height_));
}

void CImage::DrawRotaF(CVector pos, float angle, float extend, int priority,
                      unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawRotaGraphFReserve(
      graphic_handle_[num], priority,
      (int)pos.x_ - (int)CAnchor::GetIns().GetAnchorX(),
      (int)pos.y_ - (int)CAnchor::GetIns().GetAnchorY(), angle, extend, width_,
      height_));
}

void CImage::DrawRotaFwithBlend(double x1, double y1, float angle, float extend,
                                int color, int Blendmode, int value,
                                int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawRotaGraphFwithBlendReserve(
      graphic_handle_[num], priority, x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), angle, extend, color, Blendmode,
      value, width_, height_));
}

void CImage::DrawRectwithBlend(int x1, int y1, int w1, int h1, int color,
                               int Blendmode, int value, int priority,
                               unsigned int num) {
  if (num >= array_size_) return;
  if (graphic_handle_[num] == 0) abort();
  CRenderReserveList::Add(new CDrawRectGraphWithBlendReserve(
      graphic_handle_[num], priority, x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), color, Blendmode, value, w1, h1));
}

void CImage::DrawExtendWithBlend(double x1, double y1, double x2, double y2,
                                 int color, int Blendmode, int value,
                                 int priority, unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawExtendWithBlendReserve(
      graphic_handle_[num], priority, x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), x2 - CAnchor::GetIns().GetAnchorX(),
      y2 - CAnchor::GetIns().GetAnchorY(), color, Blendmode, value));
}

void CImage::DrawCircleGauge(int x, int y, double ratio, int priority,
                             unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawCircleGaugeReserve(
      graphic_handle_[num], priority, x - (int)CAnchor::GetIns().GetAnchorX(),
      y - (int)CAnchor::GetIns().GetAnchorY(), ratio, width_, height_));
}

void CImage::DrawModi(double x1, double y1, double x2, double y2, double x3,
                      double y3, double x4, double y4, int priority,
                      unsigned int num) {
  if (num >= array_size_) return;
  CRenderReserveList::Add(new CDrawModiGraphReserve(
      graphic_handle_[num], priority, x1 - CAnchor::GetIns().GetAnchorX(),
      y1 - CAnchor::GetIns().GetAnchorY(), x2 - CAnchor::GetIns().GetAnchorX(),
      y2 - CAnchor::GetIns().GetAnchorY(), x3 - CAnchor::GetIns().GetAnchorX(),
      y3 - CAnchor::GetIns().GetAnchorY(), x4 - CAnchor::GetIns().GetAnchorX(),
      y4 - CAnchor::GetIns().GetAnchorY()));
}
