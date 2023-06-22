cmake_minimum_required(VERSION 3.11)

add_subdirectory(Calc)
add_subdirectory(Costume)
add_subdirectory(Data)
add_subdirectory(Effect)
add_subdirectory(Field)
add_subdirectory(Graphic)
add_subdirectory(Input)
add_subdirectory(Mover)
add_subdirectory(Power)
add_subdirectory(Scene)
add_subdirectory(Sound)
add_library(main STATIC
 Clooper.h
 Clooper.cpp
 CMediator.h
 CParts.h
 Singleton.h
)
target_link_libraries(main PUBLIC Calc Costume Data Effect Field Graphic Input Mover Power Scene Sound)