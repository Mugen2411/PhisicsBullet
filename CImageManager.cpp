#include "CImageManager.h"

CImageManager::CImageManager()
{
    imgList["Field_Grass"] = std::make_shared<CImage>("media/graphic/mapchip/grass.png", 32, 8, 4, 32, 32);
    imgList["Field_IceFloor"] = std::make_shared<CImage>("media/graphic/mapchip/ice.png", 3, 3, 1, 32, 32);
    imgList["Field_Error"] = std::make_shared<CImage>("media/graphic/mapchip/error.png", 32, 32);

    imgList["player_komuk"] = std::make_shared<CImage>("media/graphic/character/komuk/komuk.png", 16, 4, 4, 32, 32);
    imgList["aim"] = std::make_shared<CImage>("media/graphic/system/game/aim.png", 3, 3, 1, 32, 32);
    imgList["HPGuage"] = std::make_shared<CImage>("media/graphic/system/game/HPGuage.png", 3, 1, 3, 320, 32);
    imgList["enemy_HPGuage"] = std::make_shared<CImage>("media/graphic/system/game/enemy_HPGuage.png", 2, 1, 2, 32, 4);
    imgList["enemy_marker"] = std::make_shared<CImage>("media/graphic/system/game/enemy_marker.png", 16, 16);

    imgList["effect_bulletdelete"] = std::make_shared<CImage>("media/graphic/system/game/bullet_delete.png", 8, 8, 1, 32, 32);
    imgList["effect_number1"] = std::make_shared<CImage>("media/graphic/system/font/num1.png", 44, 11, 4, 10, 10);;
    imgList["effect_number2"] = std::make_shared<CImage>("media/graphic/system/font/num2.png", 44, 11, 4, 7, 7);
    imgList["effect_number3"] = std::make_shared<CImage>("media/graphic/system/font/num3.png", 11, 11, 1, 10, 10);
    imgList["effect_flame"] = std::make_shared<CImage>("media/graphic/system/game/flame.png", 4, 2, 2, 32, 32);

    imgList["editor_cursor"] = std::make_shared<CImage>("media/graphic/system/game/Cursor.png", 32, 32);

    imgList["enemy_bud"] = std::make_shared<CImage>("media/graphic/enemy/bud/bud.png", 16, 4, 4, 32, 32);
    imgList["enemy_bud_intro"] = std::make_shared<CImage>("media/graphic/enemy/bud/intro.png", 4, 4, 1, 32, 32);;
    imgList["bullet_bud_corn"] = std::make_shared<CImage>("media/graphic/enemy/bud/corn.png", 16, 16);
    imgList["enemy_shimaenaga"] = std::make_shared<CImage>("media/graphic/enemy/shimaenaga/shimaenaga.png", 4, 4, 1, 32, 32);

    imgList["shot_uniform_homing"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/uniform/homing.png", 16, 16);
    imgList["shot_uniform_strongmagic"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/uniform/strongmagic.png", 24, 24);
}

void CImageManager::set(std::string key, std::shared_ptr<CImage> img)
{
    imgList[key] = img;
}

void CImageManager::unload()
{
    for (auto& i : imgList) {
        i.second->Release();
    }
}

std::shared_ptr<CImage> CImageManager::find(std::string key)
{
    auto itr = imgList.find(key);
    itr->second->Load();
    return itr->second;
}
