#pragma once
#include "../game_settings.hpp"
#include "../utils.hpp"
#include <raylib.h>
#include <raymath.h>
#include <vector>

class Background {
private:
    Texture2D* backgroundTexture = nullptr;
    Texture2D* cloudTexture = nullptr;
    std::vector<Vector2> clouds;
public:
    void Init(Texture2D& backgroundTexture, Texture2D& cloudTexture);
    void Update(float deltaTime);
    void Draw();
};
