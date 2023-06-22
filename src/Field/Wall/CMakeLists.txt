cmake_minimum_required(VERSION 3.11)
add_library(Wall STATIC
 CField_Wall.h CField_Wall.cpp CField_Wall_Cave.h CField_Wall_Cave.cpp
 CField_Wall_DeepWater.h CField_Wall_DeepWater.cpp CField_Wall_EnemySpawner.h CField_Wall_EnemySpawner.cpp
 CField_Wall_IceRock.h CField_Wall_IceRock.cpp CField_Wall_Log.h CField_Wall_Log.cpp 
 CField_Wall_PlayerSpawner.h CField_Wall_PlayerSpawner.cpp CField_Wall_Rock.h CField_Wall_Rock.cpp 
 CField_Wall_Tree.h CField_Wall_Tree.cpp CField_Wall_Vegetable.h CField_Wall_Vegetable.cpp
 CField_Wall_Well.h CField_Wall_Well.cpp CField_Wall_WoodFence.h CField_Wall_WoodFence.cpp 
)