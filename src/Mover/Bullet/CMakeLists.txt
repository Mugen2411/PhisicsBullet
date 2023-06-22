cmake_minimum_required(VERSION 3.11)
add_library(Bullet STATIC
 CMover_BulletBase.h CMover_BulletBase.cpp CMover_Bullet_Axe.h CMover_Bullet_Axe.cpp
 CMover_Bullet_Corn.h CMover_Bullet_Corn.cpp CMover_Bullet_CornFrost.h CMover_Bullet_CornFrost.cpp
 CMover_Bullet_Flame.h CMover_Bullet_Flame.cpp CMover_Bullet_Ice.h CMover_Bullet_Ice.cpp
 CMover_Bullet_WaterSplash.h CMover_Bullet_WaterSplash.cpp
)