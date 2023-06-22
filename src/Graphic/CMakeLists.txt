cmake_minimum_required(VERSION 3.11)
add_subdirectory(Draw)
add_subdirectory(Image)
add_library(Graphic STATIC
 CAnchor.h CAnchor.cpp CAnimationCounter.h
)
target_link_libraries(Graphic PUBLIC Draw Image)