cmake_minimum_required(VERSION 3.11)
add_library(Enemy STATIC
 CEnemyFactory.h CEnemyFactory.cpp CEnemySpawner.h CEnemySpawner.cpp
 CMover_Enemy.h CMover_Enemy.cpp CMover_Enemy_Acecorn.h CMover_Enemy_Acecorn.cpp
 CMover_Enemy_Azarashi.h CMover_Enemy_Azarashi.cpp 
 CMover_Enemy_Bud.h CMover_Enemy_Bud.cpp CMover_Enemy_CornFrosty.h CMover_Enemy_CornFrosty.cpp
 CMover_Enemy_FlameSerpent.h CMover_Enemy_FlameSerpent.cpp CMover_Enemy_Goblin.h CMover_Enemy_Goblin.cpp 
 CMover_Enemy_Shimaenaga.h CMover_Enemy_Shimaenaga.cpp CMover_Enemy_Yadokari.h CMover_Enemy_Yadokari.cpp
 CMover_Mother_Static.h CMover_Mother_Static.cpp
)