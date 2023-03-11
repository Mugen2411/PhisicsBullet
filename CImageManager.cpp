#include "CImageManager.h"

#include "CDataLoader.h"

CImageManager::CImageManager() {
  auto c = CDataLoader::GetIns().Get("resource")->GetChild("image");
  for (int i = 0;; i++) {
    auto t = c->GetChild(i);
    if (t.first == "__NULL__") break;
    if (t.second->GetChild("num")->GetInt() != 1) {
      image_list_[t.first] = std::make_shared<CImage>(
          std::string("media/graphic/") +
              t.second->GetChild("path")->GetString(),
          t.second->GetChild("num")->GetInt(),
          t.second->GetChild("xnum")->GetInt(),
          t.second->GetChild("ynum")->GetInt(),
          t.second->GetChild("w")->GetInt(), t.second->GetChild("h")->GetInt());
    } else {
      image_list_[t.first] = std::make_shared<CImage>(
          std::string("media/graphic/") +
              t.second->GetChild("path")->GetString(),
          t.second->GetChild("w")->GetInt(), t.second->GetChild("h")->GetInt());
    }
    if (!image_list_[t.first]) {
      MessageBox(NULL, (std::string("can't find image ") + t.first).c_str(),
                 "CImageManager", MB_OK);
    }
  }
}

void CImageManager::Set(std::string key, std::shared_ptr<CImage> img) {
  image_list_[key] = img;
}

void CImageManager::Unload() {
  for (auto& i : image_list_) {
    i.second->Release();
  }
}

std::shared_ptr<CImage> CImageManager::Find(std::string key) {
  auto itr = image_list_.find(key);
  itr->second->Load();
  return itr->second;
}

int HSV2RGB(float H, float S, float V) {
  float r = V;
  float g = V;
  float b = V;
  if (S > 0.0f) {
    H *= 6.0f;
    int i = (int)H;
    float f = H - (float)i;
    switch (i) {
      default:
      case 0:
        g *= 1 - S * (1 - f);
        b *= 1 - S;
        break;
      case 1:
        r *= 1 - S * f;
        b *= 1 - S;
        break;
      case 2:
        r *= 1 - S;
        b *= 1 - S * (1 - f);
        break;
      case 3:
        r *= 1 - S;
        g *= 1 - S * f;
        break;
      case 4:
        r *= 1 - S * (1 - f);
        g *= 1 - S;
        break;
      case 5:
        g *= 1 - S;
        b *= 1 - S * f;
        break;
    }

    return (int)(r * 0xFF) << 16 | (int)(g * 0xFF) << 8 | (int)(b * 0xFF);
  }
  return 0;
}