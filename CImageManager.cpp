#include "CImageManager.h"

CImageManager::CImageManager() {
  image_list_["Field_Grass"] = std::make_shared<CImage>(
      "media/graphic/mapchip/grass.png", 32, 8, 4, 32, 32);
  image_list_["Field_IceFloor"] = std::make_shared<CImage>(
      "media/graphic/mapchip/ice.png", 3, 3, 1, 32, 32);
  image_list_["Field_Tree"] = std::make_shared<CImage>(
      "media/graphic/mapchip/tree.png", 1, 1, 1, 32, 64);
  image_list_["Field_Error"] =
      std::make_shared<CImage>("media/graphic/mapchip/error.png", 32, 32);
  image_list_["Field_Cave"] = std::make_shared<CImage>(
      "media/graphic/mapchip/cave.png", 32, 8, 4, 32, 32);
  image_list_["Field_Lava"] = std::make_shared<CImage>(
      "media/graphic/mapchip/lava.png", 32, 8, 4, 32, 32);

  image_list_["player_komuk"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/komuk.png", 16, 4, 4, 32, 32);
  image_list_["aim"] = std::make_shared<CImage>("media/graphic/system/game/aim.png",
                                            3, 3, 1, 32, 32);
  image_list_["HPGuage"] = std::make_shared<CImage>(
      "media/graphic/system/game/HPGuage.png", 3, 1, 3, 320, 32);
  image_list_["enemy_HPGuage"] = std::make_shared<CImage>(
      "media/graphic/system/game/enemy_HPGuage.png", 2, 1, 2, 32, 4);
  image_list_["enemy_marker"] = std::make_shared<CImage>(
      "media/graphic/system/game/enemy_marker.png", 16, 16);
  image_list_["system_dress_guage"] = std::make_shared<CImage>(
      "media/graphic/system/game/dress_guage.png", 3, 1, 3, 160, 32);
  image_list_["system_curtain"] = std::make_shared<CImage>(
      "media/graphic/system/game/curtain.png", 2, 2, 1, 320, 480);
  image_list_["system_status_guage"] = std::make_shared<CImage>(
      "media/graphic/system/game/status_guage.png", 4, 1, 4, 240, 16);
  image_list_["system_status_name"] = std::make_shared<CImage>(
      "media/graphic/system/game/status_name.png", 6, 1, 6, 80, 16);
  image_list_["system_status_next_now"] = std::make_shared<CImage>(
      "media/graphic/system/game/status_next_now.png", 2, 2, 1, 16, 16);
  image_list_["system_costume_frame"] = std::make_shared<CImage>(
      "media/graphic/system/game/costume_frame.png", 96, 38);
  image_list_["title_face"] = std::make_shared<CImage>(
      "media/graphic/system/game/titleKomuk_x4.png", 1, 1, 1, 512, 512);
  image_list_["icon_attribute"] = std::make_shared<CImage>(
      "media/graphic/system/game/attribute.png", 6, 6, 1, 16, 16);
  image_list_["icon_weak_or_strong"] = std::make_shared<CImage>(
      "media/graphic/system/game/weak_or_strong.png", 3, 3, 1, 16, 16);
  image_list_["icon_return"] = std::make_shared<CImage>(
      "media/graphic/system/game/return_to_escape.png", 64, 64);
  image_list_["icon_passiveskill"] = std::make_shared<CImage>(
      "media/graphic/system/game/icon_passiveskill.png", 21, 7, 3, 32, 32);
  image_list_["icon_passive_covered"] = std::make_shared<CImage>(
      "media/graphic/system/game/passive_covered.png", 32, 32);
  image_list_["system_passive_frame"] = std::make_shared<CImage>(
      "media/graphic/system/game/passive_frame.png", 162, 34);
  image_list_["icon_passive_progress"] = std::make_shared<CImage>(
      "media/graphic/system/game/passive_progress.png", 6, 6, 1, 32, 16);

  image_list_["effect_bulletdelete"] = std::make_shared<CImage>(
      "media/graphic/system/game/bullet_delete.png", 8, 8, 1, 32, 32);
  image_list_["effect_number1"] = std::make_shared<CImage>(
      "media/graphic/system/font/num1.png", 48, 12, 4, 10, 10);
  image_list_["effect_number2"] = std::make_shared<CImage>(
      "media/graphic/system/font/num2.png", 48, 12, 4, 7, 7);
  image_list_["effect_number3"] = std::make_shared<CImage>(
      "media/graphic/system/font/num3.png", 11, 11, 1, 10, 10);
  image_list_["effect_number4"] = std::make_shared<CImage>(
      "media/graphic/system/font/num4.png", 11, 11, 1, 16, 32);
  image_list_["effect_flame"] = std::make_shared<CImage>(
      "media/graphic/system/game/flame.png", 4, 2, 2, 32, 32);
  image_list_["effect_bornfire"] = std::make_shared<CImage>(
      "media/graphic/system/game/bornfire.png", 4, 4, 1, 32, 32);
  image_list_["effect_wind"] = std::make_shared<CImage>(
      "media/graphic/system/game/wind.png", 2, 2, 1, 64, 64);

  image_list_["editor_cursor"] =
      std::make_shared<CImage>("media/graphic/system/game/Cursor.png", 32, 32);

  image_list_["enemy_bud"] = std::make_shared<CImage>(
      "media/graphic/enemy/bud/bud.png", 16, 4, 4, 32, 32);
  image_list_["enemy_bud_intro"] = std::make_shared<CImage>(
      "media/graphic/enemy/bud/intro.png", 4, 4, 1, 32, 32);
  image_list_["enemy_acecorn"] = std::make_shared<CImage>(
      "media/graphic/enemy/bud/ace.png", 16, 4, 4, 32, 32);
  image_list_["bullet_corn"] =
      std::make_shared<CImage>("media/graphic/enemy/bud/corn.png", 16, 16);
  image_list_["enemy_shimaenaga"] = std::make_shared<CImage>(
      "media/graphic/enemy/shimaenaga/shimaenaga.png", 4, 4, 1, 32, 32);
  image_list_["enemy_yadokari"] = std::make_shared<CImage>(
      "media/graphic/enemy/yadokari/yadokari.png", 16, 4, 4, 32, 32);
  image_list_["enemy_yadokari_intro"] = std::make_shared<CImage>(
      "media/graphic/enemy/yadokari/intro.png", 4, 4, 1, 32, 32);
  image_list_["bullet_watersplash"] = std::make_shared<CImage>(
      "media/graphic/enemy/yadokari/water.png", 32, 32);
  image_list_["enemy_goblin"] = std::make_shared<CImage>(
      "media/graphic/enemy/goblin/goblin.png", 16, 4, 4, 32, 32);
  image_list_["enemy_goblin_intro"] = std::make_shared<CImage>(
      "media/graphic/enemy/goblin/intro.png", 4, 4, 1, 32, 32);
  image_list_["bullet_axe"] =
      std::make_shared<CImage>("media/graphic/enemy/goblin/axe.png", 32, 32);
  image_list_["enemy_flameserpent"] = std::make_shared<CImage>(
      "media/graphic/enemy/flame_serpent/serpent.png", 16, 4, 4, 32, 32);

  image_list_["shot_uniform_homing"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/uniform/homing.png", 16, 16);
  image_list_["shot_uniform_strongmagic"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/uniform/strongmagic.png", 24, 24);
  image_list_["shot_festa_superball"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/festa/superball.png", 4, 4, 1, 16,
      16);
  image_list_["shot_festa_cork"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/festa/cork.png", 16, 16);
  image_list_["shot_archer_arrow"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/archer/arrow.png", 4, 1, 4, 48,
      24);
  image_list_["shot_swimsuit_iphone"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/swimsuit/phone.png", 32, 32);
  image_list_["effect_bat"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/swimsuit/bat.png", 128, 32);
  image_list_["effect_bathead"] = std::make_shared<CImage>(
      "media/graphic/character/komuk/costume/swimsuit/bat_effect.png", 48, 48);
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