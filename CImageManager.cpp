#include "CImageManager.h"

CImageManager::CImageManager()
{
    loaderList["Field_Grass"] = LG_grass;
    loaderList["Field_IceFloor"] = LG_icefloor;
    loaderList["player_komuk"] = LG_player_komuk;
    loaderList["aim"] = LG_aim;
    loaderList["effect_bulletdelete"] = LG_effect_bulletdelete;

    loaderList["enemy_bud"] = LG_enemy_bud;
    loaderList["enemy_bud_intro"] = LG_enemy_bud_intro;
    loaderList["bullet_bud_corn"] = LG_bullet_bud_corn;

    loaderList["shot_uniform_homing"] = LG_shot_uniform_homing;
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

std::shared_ptr<CImage> LG_aim()
{
    return std::make_shared<CImage>("media/graphic/system/game/aim.png", 2,2,1,32,32);
}

std::shared_ptr<CImage> LG_effect_bulletdelete()
{
    return std::make_shared<CImage>("media/graphic/system/game/bullet_delete.png", 8, 8, 1, 32, 32);
}

std::shared_ptr<CImage> LG_enemy_bud()
{
    return std::make_shared<CImage>("media/graphic/enemy/bud/bud.png", 16, 4, 4, 32, 32);
}

std::shared_ptr<CImage> LG_enemy_bud_intro()
{
    return std::make_shared<CImage>("media/graphic/enemy/bud/intro.png", 4, 4, 1, 32, 32);
}

std::shared_ptr<CImage> LG_bullet_bud_corn()
{
    return std::make_shared<CImage>("media/graphic/enemy/bud/corn.png");
}

std::shared_ptr<CImage> LG_shot_uniform_homing()
{
    return std::make_shared<CImage>("media/graphic/character/komuk/costume/uniform/homing.png");
}
