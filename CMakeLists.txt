cmake_minimum_required(VERSION 3.16)
project(RG350Launcher)

## SETTINGS ##
#
# Specify build target. Possible values: [ Computer, RG350 ]
set(TARGET_DEVICE Computer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE OFF)

if (${TARGET_DEVICE} STREQUAL RG350)
    message("-- Building for RG350!")
    set(RG350_TOOLCHAIN /mnt/d/_Dev/_RG350/buildroot-rg350-old-kernel/output)
    set(CMAKE_C_COMPILER ${RG350_TOOLCHAIN}/host/usr/bin/mipsel-rg350-linux-uclibc-gcc)
    set(CMAKE_CXX_COMPILER ${RG350_TOOLCHAIN}/host/usr/bin/mipsel-rg350-linux-uclibc-g++)

    set(SDL2_INCLUDE_DIRS ${RG350_TOOLCHAIN}/target/usr/include/SDL)
    set(SDL2_LIBRARIES ${RG350_TOOLCHAIN}/target/usr/lib/libSDL.la)
elseif(${TARGET_DEVICE} STREQUAL Computer)
    message("-- Building for PC")
    find_package(SDL2 REQUIRED)
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
else()
    message(FATAL_ERROR "Invalid target device ${TARGET_DEVICE}!")
endif()


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
        source/ui/view/grid.cpp
        source/ui/view/page_switcher.cpp)

include_directories(${SDL2_INCLUDE_DIRS} include libs/nanovg libs/glad/include)
target_link_libraries(RG350Launcher ${SDL2_LIBRARIES})