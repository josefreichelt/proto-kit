#include "utils.hpp"

Vector2 GetScaledTextureDimensions(Texture2D& texture) {
    Vector2 dimensions;
    dimensions.x = texture.width * GameSettings::scaleFactor;
    dimensions.y = texture.height * GameSettings::scaleFactor;
    return dimensions;
}

Vector2 GetScreenCenter() {
    Vector2 center;
    center.x = static_cast<float>(GameSettings::screenWidth) / 2;
    center.y = static_cast<float>(GameSettings::screenHeight) / 2;
    return center;
}

Vector2 GetScreenDimension() {
    Vector2 dimensions;
    dimensions.x = static_cast<float>(GameSettings::screenWidth);
    dimensions.y = static_cast<float>(GameSettings::screenHeight);
    return dimensions;
}

bool GetScreenDimensionChanged() {
    static Vector2 lastScreenDimension = GetScreenDimension();
    Vector2 currentScreenDimension = GetScreenDimension();
    if (lastScreenDimension.x != currentScreenDimension.x || lastScreenDimension.y != currentScreenDimension.y) {
        lastScreenDimension = currentScreenDimension;
        return true;
    }
    return false;
}
