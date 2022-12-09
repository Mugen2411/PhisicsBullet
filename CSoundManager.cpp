#include "CSoundManager.h"

CSoundManager::CSoundManager()
{
    sndList["player_dead"] = std::make_shared<CSound>("media/sound/se/player_dead.wav");
    sndList["player_hit"] = std::make_shared<CSound>("media/sound/se/player_hit.wav");
    sndList["enemy_kill"] = std::make_shared<CSound>("media/sound/se/enemy_kill.wav");
    sndList["enemy_hit"] = std::make_shared<CSound>("media/sound/se/enemy_hit.wav");
    sndList["shot_superball"] = std::make_shared<CSound>("media/sound/se/superball.wav");
    sndList["shot_cork"] = std::make_shared<CSound>("media/sound/se/cork.wav");
    sndList["cursor"] = std::make_shared<CSound>("media/sound/se/cursor.wav");
    sndList["money"] = std::make_shared<CSound>("media/sound/se/money.wav");
    sndList["success"] = std::make_shared<CSound>("media/sound/se/success.wav");
    sndList["bat_swing"] = std::make_shared<CSound>("media/sound/se/bat_swing.wav");
    sndList["throw"] = std::make_shared<CSound>("media/sound/se/throw.wav");
    sndList["glassBreak"] = std::make_shared<CSound>("media/sound/se/glassBreak.wav");
    sndList["little_fire"] = std::make_shared<CSound>("media/sound/se/little_fire.wav");
    sndList["little_magic"] = std::make_shared<CSound>("media/sound/se/little_magic.wav");
    sndList["middle_magic"] = std::make_shared<CSound>("media/sound/se/middle_magic.wav");
    sndList["pretty_throw"] = std::make_shared<CSound>("media/sound/se/pretty_throw.wav");
    sndList["splash"] = std::make_shared<CSound>("media/sound/se/splash.wav");

    sndList["bgm"] = std::make_shared<CSound>("media/sound/bgm/farm.ogg");
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
