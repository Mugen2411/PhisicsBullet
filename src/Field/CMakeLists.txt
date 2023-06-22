cmake_minimum_required(VERSION 3.11)
add_subdirectory(Wall)
add_subdirectory(Floor)
add_subdirectory(Decoration)
add_library(Field STATIC
 CField.h CField.cpp CFieldFactory.h CFieldFactory.cpp
 CFieldHolder.h CFieldHolder.cpp CFieldParent.h CFieldParent.cpp
)
target_link_libraries(Field PUBLIC Wall Floor Decoration)