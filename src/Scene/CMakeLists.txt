cmake_minimum_required(VERSION 3.11)
add_library(Scene STATIC
 CGameMediator.h CGameMediator.cpp CMapEditor.h CMapEditor.cpp
 SceneManager.h SceneManager.cpp Scene_Abstract.h Scene_Abstract.cpp
 Scene_Gameclear.h Scene_Gameclear.cpp Scene_Gameover.h Scene_Gameover.cpp 
 Scene_Option.h Scene_Option.cpp Scene_Stageclear.h Scene_Stageclear.cpp
 Scene_Title.h Scene_Title.cpp Scene_Upgrade.h Scene_Upgrade.cpp
)