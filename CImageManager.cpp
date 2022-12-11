#include "CImageManager.h"

CImageManager::CImageManager()
{
    imgList["Field_Grass"] = std::make_shared<CImage>("media/graphic/mapchip/grass.png", 32, 8, 4, 32, 32);
    imgList["Field_IceFloor"] = std::make_shared<CImage>("media/graphic/mapchip/ice.png", 3, 3, 1, 32, 32);
    imgList["Field_Tree"] = std::make_shared<CImage>("media/graphic/mapchip/tree.png", 1, 1, 1, 32, 64);
    imgList["Field_Error"] = std::make_shared<CImage>("media/graphic/mapchip/error.png", 32, 32);

    imgList["player_komuk"] = std::make_shared<CImage>("media/graphic/character/komuk/komuk.png", 16, 4, 4, 32, 32);
    imgList["aim"] = std::make_shared<CImage>("media/graphic/system/game/aim.png", 3, 3, 1, 32, 32);
    imgList["HPGuage"] = std::make_shared<CImage>("media/graphic/system/game/HPGuage.png", 3, 1, 3, 320, 32);
    imgList["enemy_HPGuage"] = std::make_shared<CImage>("media/graphic/system/game/enemy_HPGuage.png", 2, 1, 2, 32, 4);
    imgList["enemy_marker"] = std::make_shared<CImage>("media/graphic/system/game/enemy_marker.png", 16, 16);
    imgList["system_dress_guage"] = std::make_shared<CImage>("media/graphic/system/game/dress_guage.png", 3, 1, 3, 160, 32);
    imgList["system_curtain"] = std::make_shared<CImage>("media/graphic/system/game/curtain.png", 2, 2, 1, 320, 480);
    imgList["system_status_guage"] = std::make_shared<CImage>("media/graphic/system/game/status_guage.png", 4, 1, 4, 240, 16);
    imgList["system_status_name"] = std::make_shared<CImage>("media/graphic/system/game/status_name.png", 6, 1, 6, 80, 16);
    imgList["system_status_next_now"] = std::make_shared<CImage>("media/graphic/system/game/status_next_now.png", 2, 2, 1, 16, 16);
    imgList["system_costume_frame"] = std::make_shared<CImage>("media/graphic/system/game/costume_frame.png", 96, 38);
    imgList["title_face"] = std::make_shared<CImage>("media/graphic/system/game/titleKomuk_x4.png", 1, 1, 1, 512, 512);
    imgList["icon_attribute"] = std::make_shared<CImage>("media/graphic/system/game/attribute.png", 6, 6, 1, 16, 16);
    imgList["icon_weak_or_strong"] = std::make_shared<CImage>("media/graphic/system/game/weak_or_strong.png", 3, 3, 1, 16, 16);
    imgList["icon_return"] = std::make_shared<CImage>("media/graphic/system/game/return_to_escape.png", 64, 64);

    imgList["effect_bulletdelete"] = std::make_shared<CImage>("media/graphic/system/game/bullet_delete.png", 8, 8, 1, 32, 32);
    imgList["effect_number1"] = std::make_shared<CImage>("media/graphic/system/font/num1.png", 48, 12, 4, 10, 10);
    imgList["effect_number2"] = std::make_shared<CImage>("media/graphic/system/font/num2.png", 48, 12, 4, 7, 7);
    imgList["effect_number3"] = std::make_shared<CImage>("media/graphic/system/font/num3.png", 11, 11, 1, 10, 10);
    imgList["effect_flame"] = std::make_shared<CImage>("media/graphic/system/game/flame.png", 4, 2, 2, 32, 32);

    imgList["editor_cursor"] = std::make_shared<CImage>("media/graphic/system/game/Cursor.png", 32, 32);

    imgList["enemy_bud"] = std::make_shared<CImage>("media/graphic/enemy/bud/bud.png", 16, 4, 4, 32, 32);
    imgList["enemy_bud_intro"] = std::make_shared<CImage>("media/graphic/enemy/bud/intro.png", 4, 4, 1, 32, 32);;
    imgList["bullet_bud_corn"] = std::make_shared<CImage>("media/graphic/enemy/bud/corn.png", 16, 16);
    imgList["enemy_shimaenaga"] = std::make_shared<CImage>("media/graphic/enemy/shimaenaga/shimaenaga.png", 4, 4, 1, 32, 32);
    imgList["enemy_yadokari"] = std::make_shared<CImage>("media/graphic/enemy/yadokari/yadokari.png", 16, 4, 4, 32, 32);
    imgList["bullet_yadokari_watersplash"] = std::make_shared<CImage>("media/graphic/enemy/yadokari/water.png", 32, 32);

    imgList["shot_uniform_homing"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/uniform/homing.png", 16, 16);
    imgList["shot_uniform_strongmagic"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/uniform/strongmagic.png", 24, 24);
    imgList["shot_festa_superball"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/festa/superball.png", 4, 4, 1, 16, 16);
    imgList["shot_festa_cork"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/festa/cork.png", 16, 16);
    imgList["shot_archer_arrow"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/archer/arrow.png", 4, 1, 4, 48, 24);
    imgList["shot_swimsuit_iphone"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/swimsuit/phone.png", 32, 32);
    imgList["effect_bat"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/swimsuit/bat.png", 128, 32);
    imgList["effect_bathead"] = std::make_shared<CImage>("media/graphic/character/komuk/costume/swimsuit/bat_effect.png", 48, 48);
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
}