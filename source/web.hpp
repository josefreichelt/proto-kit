/**
 * Helper file to handle web specific callbacks and functions.
 *
 */
#pragma once
#ifdef PLATFORM_WEB

#include <emscripten.h>
#include <emscripten/html5.h>
#include <raylib.h>

#include "game_settings.hpp"

void RegisterEmscriptenCallbacks();
void HandleEmscriptenCanvasResize(void* userData);

#endif
