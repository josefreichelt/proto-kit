
#pragma once
#include "../game_settings.hpp"
#include "paddle.hpp"
#include "../utils.hpp"
#include <raygui.h>
#include <raylib.h>
#include <raymath.h>
#include <string>

class Ball {
private:
    Texture2D* ballTexture = nullptr;
    Sound* hitSound = nullptr;
    Sound* bounceSound = nullptr;
    int* score = nullptr;
    bool canMove = true;

    Vector2 position { 100, 400 };
    Vector2 velocity { 0, 0 };
    float radius { 15 };
    float mass { 4 };
    float maxSpeed = 10;
    float rotation = 0;

public:
    // Methods
    void Init(Texture2D& ballTexture, Sound& hitSound, Sound& bounceSound, int& score);
    void Update(float deltaTime);
    void Draw(Texture2D& ballTexture);
    bool IsCollidingWithPaddle(Paddle& paddle);
    bool GetCanMove() const;
    void Reset();
};
