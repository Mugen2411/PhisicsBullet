#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
    sndList["kill_enemy"] = std::make_shared<CSound>("media/sound/se/kill_enemy.wav");
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
