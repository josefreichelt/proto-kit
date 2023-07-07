#include "game_settings.hpp"

#ifdef PLATFORM_WEB
int GameSettings::screenWidth = 960;
int GameSettings::screenHeight = 640;
#else
int GameSettings::screenWidth = 1280;
int GameSettings::screenHeight = 720;
#endif

#ifdef DEBUG
bool GameSettings::showDebug = true;
#else
bool GameSettings::showDebug = false;
#endif

const std::string GameSettings::GAME_TITLE = "Proto-Kit";
const int GameSettings::TARGET_FPS = 60;
float GameSettings::scaleFactor = 1.0f;
int GameSettings::baseFontSize = GameSettings::screenHeight / 36;
