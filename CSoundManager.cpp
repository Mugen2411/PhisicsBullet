#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
    sndList["player_dead"] = std::make_shared<CSound>("media/sound/se/player_dead.wav");
    sndList["player_hit"] = std::make_shared<CSound>("media/sound/se/player_hit.wav");
    sndList["enemy_kill"] = std::make_shared<CSound>("media/sound/se/enemy_kill.wav");
    sndList["enemy_hit"] = std::make_shared<CSound>("media/sound/se/enemy_hit.wav");
    sndList["shot_superball"] = std::make_shared<CSound>("media/sound/se/superball.wav");
    sndList["shot_cork"] = std::make_shared<CSound>("media/sound/se/cork.wav");

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
