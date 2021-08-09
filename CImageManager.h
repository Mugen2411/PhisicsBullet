#pragma once
#include "Singleton.h"
#include "CImage.h"
#include <string>
#include <map>
#include <memory>

class CImageManager :
    public Singleton<CImageManager>
{
    std::map<std::string, std::shared_ptr<CImage>> imgList;
    std::map<std::string, std::shared_ptr<CImage>(*)()> loaderList;
public:
    CImageManager();
    void set(std::string key, std::shared_ptr<CImage> img);
    std::shared_ptr<CImage> find(std::string key);

    void Render();
};

//�ȉ����[�_�[�֐����X�g(LG��LoadGraphic�̗�)
std::shared_ptr<CImage> LG_grass();
std::shared_ptr<CImage> LG_icefloor();
std::shared_ptr<CImage> LG_player_komuk();
std::shared_ptr<CImage> LG_aim();

std::shared_ptr<CImage> LG_enemy_bud();
std::shared_ptr<CImage> LG_enemy_bud_intro();
std::shared_ptr<CImage> LG_bullet_bud_corn();

std::shared_ptr<CImage> LG_shot_uniform_homing();

