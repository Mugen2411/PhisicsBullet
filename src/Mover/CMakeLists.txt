cmake_minimum_required(VERSION 3.11)
add_subdirectory(Coin)
add_subdirectory(Bullet)
add_subdirectory(Enemy)
add_subdirectory(Shot)
add_library(Mover STATIC
 CMover.h CMover.cpp CMoverParent.h CMoverParent.cpp CMover_Player.h CMover_Player.cpp
)
target_link_libraries(Mover PUBLIC Coin Bullet Enemy Shot)