#pragma once
#include "Singleton.h"
#include "CImage.h"
#include <string>
#include <map>
#include <memory>
#include <DxLib.h>

class CImageManager :
    public Singleton<CImageManager>
{
    std::map<std::string, std::shared_ptr<CImage>, std::less<>> imgList;
    std::map<std::string, std::shared_ptr<CImage>(*)(), std::less<>> loaderList;
public:
    CImageManager();
    void set(std::string key, std::shared_ptr<CImage> img);
    void unload();
    std::shared_ptr<CImage> find(std::string key);

    enum BLENDMODE {
        BM_NONE = DX_BLENDMODE_NOBLEND,
        BM_ADD = DX_BLENDMODE_ADD,
        BM_SUB = DX_BLENDMODE_SUB,
        BM_ALPHA = DX_BLENDMODE_ALPHA,
        BM_MUL = DX_BLENDMODE_MUL
    };

    void Render()const;
};

//以下ローダー関数リスト(LGはLoadGraphicの略)
std::shared_ptr<CImage> LG_field_grass();
std::shared_ptr<CImage> LG_field_icefloor();
std::shared_ptr<CImage> LG_player_komuk();
std::shared_ptr<CImage> LG_aim();
std::shared_ptr<CImage> LG_effect_bulletdelete();
std::shared_ptr<CImage> LG_HPGuage();
std::shared_ptr<CImage> LG_enemy_HPGuage();

std::shared_ptr<CImage> LG_effect_number1();
std::shared_ptr<CImage> LG_effect_number2();
std::shared_ptr<CImage> LG_effect_number3();

std::shared_ptr<CImage> LG_editor_cursor();

std::shared_ptr<CImage> LG_enemy_bud();
std::shared_ptr<CImage> LG_enemy_bud_intro();
std::shared_ptr<CImage> LG_bullet_bud_corn();

std::shared_ptr<CImage> LG_shot_uniform_homing();
std::shared_ptr<CImage> LG_shot_uniform_strongmagic();

