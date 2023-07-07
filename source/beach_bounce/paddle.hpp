
#pragma once
#include "../game_settings.hpp"
#include "../utils.hpp"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>
#include <string>

class Paddle {
private:
    Texture2D* paddleTexture = nullptr;
    bool isCollidingWithBall = false;
    float collisionAnimationTimer = 0;
    float bottomHeight = 50;

public:
    Vector2 position { 100, 400 };
    Vector2 size { 150, 20 };
    float speed = 600;

    // Methods
    void Init(Texture2D& paddleTexture);
    void Update(float deltaTime);
    void Draw(Texture2D& paddleTexture);
    void AnimateCollision();
    void Reset();
};
