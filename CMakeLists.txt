set(CMAKE_VERBOSE_MAKEFILE 1)
cmake_minimum_required(VERSION 3.5...3.11)
project(Makeover)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Makeover)
set(CMAKE_CXX_STANDARD 20)

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

# DxLibが置かれているディレクトリを指定
set( DXLIB_DIR "${PROJECT_SOURCE_DIR}/DxLib_VC/プロジェクトに追加すべきファイル_VC用" )
message((${DXLIB_DIR}))
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(${DXLIB_DIR})
link_directories(${DXLIB_DIR} )

add_subdirectory(src)
add_executable(Makeover WIN32 src/main.cpp Resource.rc)
target_link_libraries(Makeover PUBLIC main)