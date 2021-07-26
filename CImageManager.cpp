#include "CImageManager.h"

CImageManager::CImageManager()
{
    loaderList["Field_Grass"] = LG_grass;
    loaderList["Field_IceFloor"] = LG_icefloor;
    loaderList["player_komuk"] = LG_player_komuk;
}

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
    set(key, loaderList[key]());
    return imgList.find(key)->second;
}

std::shared_ptr<CImage> LG_grass()
{
    return std::make_shared<CImage>("media/graphic/mapchip/grass.png", 5, 5, 1, 32, 32);
}

std::shared_ptr<CImage> LG_icefloor()
{
    return std::make_shared<CImage>("media/graphic/mapchip/ice.png", 3, 3, 1, 32, 32);
}

std::shared_ptr<CImage> LG_player_komuk()
{
    return std::make_shared<CImage>("media/graphic/character/komuk/komuk.png", 16, 4, 4, 32, 32);
}
