#pragma once

#include "result.hpp"

constexpr u32 ModuleSDL = 1;
constexpr u32 ModuleNVG = 2;

constexpr Result ResultSuccess(0);

constexpr Result ResultSDLInitFailed(ModuleSDL, 1);
constexpr Result ResultSDLWindowCreationFailed(ModuleSDL, 2);
constexpr Result ResultSDLGLCreationFailed(ModuleSDL, 3);