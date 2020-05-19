cmake_minimum_required(VERSION 3.16)
project(RG350Launcher)

## SETTINGS ##
#
# Specify build target. Possible values: [ Computer, RG350 ]
set(TARGET_DEVICE Computer)
# RG350 Toolchain path
set(RG350_TOOLCHAIN "/mnt/d/_Dev/_RG350/buildroot-2020.05-rc1/buildroot-2020.05-rc1/output")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE OFF)

if (${TARGET_DEVICE} STREQUAL RG350)
    message("-- Building for RG350!")
    set(CMAKE_C_COMPILER ${RG350_TOOLCHAIN}/host/bin/mipsel-linux-gcc)
    set(CMAKE_CXX_COMPILER ${RG350_TOOLCHAIN}/host/bin/mipsel-linux-g++)

    set(SDL2_INCLUDE_DIRS ${RG350_TOOLCHAIN}/target/usr/include/SDL2)
    set(SDL2_LIBRARIES ${RG350_TOOLCHAIN}/target/usr/lib/libSDL2.a)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lpthread -lstdc++ -lc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
elseif(${TARGET_DEVICE} STREQUAL Computer)
    message("-- Building for PC")
    find_package(SDL2 REQUIRED)
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
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
        source/ui/view/image_text_button.cpp
        source/ui/application.cpp
        source/gui/page/page_emulators.cpp
        source/gui/page/page_homebrew.cpp
        source/gui/page/page_settings.cpp
        source/dev/device.cpp
        source/ui/view/grid.cpp
        source/ui/view/page_switcher.cpp)

include_directories(${SDL2_INCLUDE_DIRS} ${STDLIB_INCLUDE_DIRS} include libs/nanovg libs/glad/include)
target_link_libraries(RG350Launcher ${SDL2_LIBRARIES})