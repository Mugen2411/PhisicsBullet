cmake_minimum_required(VERSION 3.11)
add_subdirectory(Archer)
add_subdirectory(Burner)
add_subdirectory(Chinese)
add_subdirectory(Festa)
add_subdirectory(FireFighter)
add_subdirectory(Swimsuit)
add_subdirectory(Uniform)
add_library(Shot STATIC
 CMover_ShotBase.h CMover_ShotBase.cpp
)
target_link_libraries(Shot PUBLIC Archer Burner Chinese Festa FireFighter Swimsuit Uniform)