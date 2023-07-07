#include "ball.hpp"
#include <iostream>

void Ball::Init(Texture2D& ballTexture, Sound& hitSound, Sound& bounceSound, int& score)
{
    this->ballTexture = &ballTexture;
    this->hitSound = &hitSound;
    this->bounceSound = &bounceSound;
    this->score = &score;
    Reset();
}

void Ball::Update(float deltaTime)
{
    auto dir = Vector2Normalize(velocity);

    if (canMove) {
        velocity.y += (GRAVITY * (mass)) * deltaTime;
    }
    // Bounce off the wall on left or right
    if (position.x - radius < 0 || position.x + radius > GameSettings::screenWidth) {
        velocity.x *= -1;
        PlaySound(*hitSound);
    }
    // Bounce off bottom
    if (position.y + radius > GameSettings::screenHeight && velocity.y > 0) {
        velocity.y -= mass * 4;
        *score = 0;
        if (velocity.y <= 0) {
            velocity.y = 0;
            velocity.x = 0;
            position.y = GameSettings::screenHeight - radius;
            canMove = false;
        } else {
            velocity.y *= -1;
            velocity.x *= 0.5;
            PlaySound(*hitSound);
        }
    }

    rotation += velocity.x * deltaTime;
    if (rotation > 360) {
        rotation = 0;
    }

    if (canMove) {
        velocity.y = Clamp(velocity.y, -maxSpeed, maxSpeed);
        position = Vector2Add(position, Vector2Scale(velocity, deltaTime));
    }

    static bool followMouse = false;
    // Out of bounds reset
    if (position.x + radius < 0 || position.x - radius > GameSettings::screenWidth || position.y - radius > GameSettings::screenHeight) {
        Reset();
    }

    if (GameSettings::showDebug && IsKeyPressed(KEY_T)) {
        followMouse = !followMouse;
    }
    if (followMouse) {
        velocity = { 0, 0 };
        rotation = 0;
        auto mousePos = GetMousePosition();
        position = mousePos;
    }
}

void Ball::Draw(Texture2D& ballTexture)
{
    auto texRecSource = Rectangle { 0, 0, static_cast<float>(ballTexture.width), static_cast<float>(ballTexture.height) };
    auto texRecDest = Rectangle { position.x, position.y, radius * 2, radius * 2 };
    DrawTexturePro(ballTexture, texRecSource, texRecDest, Vector2 { radius, radius }, rotation, WHITE);

    if (GameSettings::showDebug) {
        DrawRectangleLines(position.x - radius, position.y - radius, radius * 2, radius * 2, RED);
        DrawCircleLines(position.x, position.y, radius, BLUE);
        DrawLineEx(position, Vector2Add(position, Vector2Scale(velocity, 1)), 5, DARKBROWN);

        GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0x101010FF);
        GuiSetStyle(LABEL, TEXT_SIZE, 20);
        std::string ballposText = "Position: " + std::to_string(static_cast<int>(position.x)) + " : " + std::to_string(static_cast<int>(position.y));
        GuiLabel({ 10, 30, static_cast<float>(MeasureText(ballposText.c_str(), 12)), 30 }, ballposText.c_str());
        std::string radiusText = "Radius: " + std::to_string(static_cast<int>(radius));
        GuiLabel({ 10, 40, static_cast<float>(MeasureText(radiusText.c_str(), 12)), 30 }, radiusText.c_str());
        std::string massText = "Mass: " + std::to_string(mass);
        GuiLabel({ 10, 60, static_cast<float>(MeasureText(massText.c_str(), 12)), 30 }, massText.c_str());
        std::string velocityText = "Velocity: " + std::to_string(velocity.x) + " : " + std::to_string(velocity.y);
        GuiLabel({ 10, 70, static_cast<float>(MeasureText(velocityText.c_str(), 12)), 30 }, velocityText.c_str());
        std::string velocityDirText = "Velocity Direction: " + std::to_string(Vector2Normalize(velocity).x) + " : " + std::to_string(Vector2Normalize(velocity).y);
        GuiLabel({ 10, 80, static_cast<float>(MeasureText(velocityDirText.c_str(), 12)), 30 }, velocityDirText.c_str());
    }
}

bool Ball::IsCollidingWithPaddle(Paddle& paddle)
{
    if (CheckCollisionCircleRec(position, radius, Rectangle { paddle.position.x - paddle.size.x / 2, paddle.position.y - paddle.size.y / 2, paddle.size.x, paddle.size.y })) {
        if (position.y > paddle.position.y) {
            return false;
        }
        auto bouncedDirection = velocity;
        if (velocity.y > 0) {
            bouncedDirection.y = Clamp(-1 * abs(velocity.y) * maxSpeed, -maxSpeed, maxSpeed);
            (*score)++;
        } else {
            bouncedDirection.y = Clamp(abs(velocity.y), -maxSpeed, maxSpeed);
        }
        bouncedDirection.x = Clamp(((position.x - paddle.position.x) / (paddle.size.x / 2)) * maxSpeed, -maxSpeed, maxSpeed);

        velocity = bouncedDirection;
        PlaySound(*bounceSound);
        paddle.AnimateCollision();
        return true;
    }
    return false;
}

bool Ball::GetCanMove() const
{
    return canMove;
}

void Ball::Reset()
{
    *score = 0;
    position.x = GameSettings::screenWidth / 2;
    position.y = GameSettings::screenHeight / 2;
    maxSpeed = 500;
    radius = GetScaledTextureDimensions(*ballTexture).x / 2;
    mass = 50;
    velocity.x = 0;
    velocity.y = maxSpeed / 2;
    canMove = true;
}
