#pragma once
#include <string>

struct GameSettings {
    static int screenWidth;
    static int screenHeight;
    static const std::string GAME_TITLE;
    static const int TARGET_FPS;
    static bool showDebug;
    static float scaleFactor;
    static int baseFontSize;
};
const float GRAVITY = 9.8f;
