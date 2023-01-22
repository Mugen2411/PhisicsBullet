#pragma once
#include <DxLib.h>

#include <map>
#include <memory>
#include <string>

#include "CImage.h"
#include "Singleton.h"

class CImageManager : public Singleton<CImageManager> {
 public:

  enum BlendMode {
    kNone = DX_BLENDMODE_NOBLEND,
    kAdd = DX_BLENDMODE_ADD,
    kSub = DX_BLENDMODE_SUB,
    kAlpha = DX_BLENDMODE_ALPHA,
    kMult = DX_BLENDMODE_MUL
  };

  void Set(std::string key, std::shared_ptr<CImage> img);
  void Unload();
  std::shared_ptr<CImage> Find(std::string key);

  void Render() const;

 protected:
  CImageManager();

  private:
  std::map<std::string, std::shared_ptr<CImage>, std::less<>> image_list_;

  friend class Singleton<CImageManager>;
};

int HSV2RGB(float H, float S, float V);