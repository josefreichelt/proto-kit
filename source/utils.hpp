#pragma once
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>

#include "game_settings.hpp"

Vector2 GetScaledTextureDimensions(Texture2D& texture);
Vector2 GetScreenCenter();
Vector2 GetScreenDimension();
bool GetScreenDimensionChanged();
