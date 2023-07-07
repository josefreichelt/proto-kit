/**
 * Main game class
 * This is the core of the entire applioation.
 */
#pragma once
#include <iostream>
#include <raylib.h>

#include "beach_bounce/background.hpp"
#include "beach_bounce/ball.hpp"
#include "beach_bounce/paddle.hpp"
#include "game_settings.hpp"
#include "utils.hpp"

#ifdef PLATFORM_WEB
#include "web.hpp"
#endif

enum class GameState {
    Title,
    Playing,
    BallLost,
};

class Game {
private:
    // Assets
    Texture2D ballTexture;
    Texture2D paddleTexture;
    Texture2D backgroundTexture;
    Texture2D titleTexture;
    Texture2D cloudTexture;

    Sound bounceSound;
    Sound hitSound;
    // Game related members
    GameState gameState = GameState::Title;
    int score = 0;
    int maxScore = 0;
    int scoreLastRound = 0;
    // Game Objects
    Ball ball;
    Paddle paddle;
    Background background;

private:
    void Update(float deltaTime);
    void Draw();

    void DrawTitle();
    void DrawScore();
    void DrawBallLost();

    void SetDisplayScale();

public:
    void Init();
    void Run();
    void GameLoop();
    void Quit();
};
