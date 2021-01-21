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
public:
    void set(std::string key, std::shared_ptr<CImage> img);
    std::shared_ptr<CImage> find(std::string key);
};

