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

