#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
    sndList["kill_enemy"] = std::make_shared<CSound>("media/sound/se/kill_enemy.wav");

    sndList["bgm_test"] = std::make_shared<CSound>("media/sound/bgm/NaoGame02.ogg");
}

void CSoundManager::unload()
{
    for (auto& i : sndList) {
        i.second->Release();
    }
}

std::shared_ptr<CSound> CSoundManager::find(std::string key)
{
    auto itr = sndList[key];
    itr->Load();
    return itr;
}
