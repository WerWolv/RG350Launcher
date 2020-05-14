cmake_minimum_required(VERSION 3.16)
project(RG350Launcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

find_package(SDL2 REQUIRED)

add_executable(RG350Launcher
        libs/nanovg/nanovg.c
        libs/glad/src/gl.c

        source/main.cpp
        source/ui/gui.cpp
        source/ui/view/view.cpp
        source/ui/view/debug_rectangle.cpp
        source/ui/view/header.cpp
        source/ui/view/image.cpp
        source/ui/view/image_button.cpp
        source/ui/application.cpp
        source/gui/page/page_emulators.cpp
        source/gui/page/page_homebrew.cpp
        source/gui/page/page_settings.cpp
        source/dev/device.cpp
        include/dev/device_screen.hpp source/ui/view/grid.cpp include/ui/style.hpp include/ui/view/page_switcher.hpp source/ui/view/page_switcher.cpp)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

include_directories(${SDL2_INCLUDE_DIRS} include libs/nanovg libs/glad/include)
target_link_libraries(RG350Launcher ${SDL2_LIBRARIES})