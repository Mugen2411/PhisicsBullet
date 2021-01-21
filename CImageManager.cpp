#include "CImageManager.h"

void CImageManager::set(std::string key, std::shared_ptr<CImage> img)
{
    imgList[key] = img;
}

std::shared_ptr<CImage> CImageManager::find(std::string key)
{
    auto itr = imgList.find(key);
    if (itr != imgList.end()) {
        return itr->second;
    }
    return nullptr;
}
