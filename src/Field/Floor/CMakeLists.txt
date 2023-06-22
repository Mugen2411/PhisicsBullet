cmake_minimum_required(VERSION 3.11)
add_library(Floor STATIC
 CField_Cave.h CField_Cave.cpp CField_Dirt.h CField_Dirt.cpp 
 CField_Error.h CField_Error.cpp CField_Grass.h CField_Grass.cpp
 CField_IceFloor.h CField_IceFloor.cpp CField_Lava.h CField_Lava.cpp CField_Void.h CField_Void.cpp 
)