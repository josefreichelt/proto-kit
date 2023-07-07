#include "paddle.hpp"
#include <iostream>

void Paddle::Init(Texture2D& paddleTexture)
{
    this->paddleTexture = &paddleTexture;

    Reset();
}

void Paddle::Update(float deltaTime)
{
    // Bounce animation
    if (collisionAnimationTimer > 0) {
        collisionAnimationTimer -= deltaTime;
        position.y += 20 * deltaTime;
    } else {
        if (position.y > bottomHeight) {
            position.y -= 10 * deltaTime;
        } else {
            position.y = bottomHeight;
        }
    }
    // Keyboard input
    if (IsKeyDown(KEY_LEFT)) {
        position.x -= speed * deltaTime;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        position.x += speed * deltaTime;
    }
    // Mouse input
    float mouseSpeedX = GetMouseDelta().x;
    if (mouseSpeedX > 0 || mouseSpeedX < 0) {
        position.x = GetMouseX();
    } else if (IsGestureDetected(GESTURE_DRAG) || IsGestureDetected(GESTURE_HOLD)) {
        position.x = GetTouchX();
    }

    // Clamp to screen
    if (position.x - size.x / 2 < 0) {
        position.x = 0 + size.x / 2;
    }
    if (position.x + size.x / 2 > GameSettings::screenWidth) {
        position.x = GameSettings::screenWidth - size.x / 2;
    }
}

void Paddle::Draw(Texture2D& paddleTex)
{
    auto texRecSource = Rectangle { 0, 0, static_cast<float>(paddleTex.width), static_cast<float>(paddleTex.height) };
    auto texRecDest = Rectangle { position.x, position.y, size.x, size.y };
    DrawTexturePro(paddleTex, texRecSource, texRecDest, Vector2 { size.x / 2, size.y / 2 }, 0, WHITE);

    if (GameSettings::showDebug) {
        DrawRectangleLines(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, RED);
    }
}

void Paddle::AnimateCollision()
{
    collisionAnimationTimer = 0.1f;
}

void Paddle::Reset()
{
    collisionAnimationTimer = 0;
    size = GetScaledTextureDimensions(*paddleTexture);
    bottomHeight = GameSettings::screenHeight - size.y - size.y / 2;
    position.x = GameSettings::screenWidth / 2 - size.x / 2;
    position.y = bottomHeight;
}
