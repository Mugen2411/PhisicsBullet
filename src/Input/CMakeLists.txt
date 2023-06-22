cmake_minimum_required(VERSION 3.11)
add_library(Input STATIC
 CControllerFactory.h CControllerFactory.cpp CKeyInputManager.h CKeyInputManager.cpp
 CSTGInputManager.h CSTGInputManager.cpp KeyManager.h KeyManager.cpp include_InputManagers.h
)