#include "game.hpp"
// Has to be defined last once in a cpp file, because of raygui magic
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void Game::Run()
{
    Init();
    while (!WindowShouldClose()) {
        GameLoop();
    }
    Quit();
}

/**
 * Initialize window, load assets and set up game objects.
 */
void Game::Init()
{
#ifdef DEBUG
    SetTraceLogLevel(LOG_DEBUG);
#else
    SetTraceLogLevel(LOG_NONE);
#endif

// Initialization of Window and Audio
#ifdef PLATFORM_WEB
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
#else
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
#endif

    InitWindow(GameSettings::screenWidth, GameSettings::screenHeight, GameSettings::GAME_TITLE.c_str());
    InitAudioDevice();
    SetMasterVolume(0.25);
    SetTargetFPS(GameSettings::TARGET_FPS);

    // Load assets
    ballTexture = LoadTexture("assets/beach-ball16.png");
    cloudTexture = LoadTexture("assets/cloud.png");
    paddleTexture = LoadTexture("assets/paddle.png");
    backgroundTexture = LoadTexture("assets/beach-bg.png");
    titleTexture = LoadTexture("assets/title.png");
    bounceSound = LoadSound("assets/bounce.wav");
    hitSound = LoadSound("assets/hit.wav");

    // Setup game objects
    SetDisplayScale();
    background.Init(backgroundTexture, cloudTexture);
    paddle.Init(paddleTexture);
    ball.Init(ballTexture, hitSound, bounceSound, score);

#ifdef PLATFORM_WEB
    RegisterEmscriptenCallbacks();
#endif
}

void Game::GameLoop()
{
    if (IsWindowResized()) {
        GameSettings::screenWidth = GetRenderWidth();
        GameSettings::screenHeight = GetRenderHeight();
        SetDisplayScale();
    }
    Update(GetFrameTime());
    Draw();
}

void Game::Update(float deltaTime)
{
#ifdef DEBUG
    if (IsKeyPressed(KEY_F3)) {
        GameSettings::showDebug = !GameSettings::showDebug;
    }
#endif

    switch (gameState) {
    case GameState::Title: {
        if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gameState = GameState::Playing;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                paddle.position.x = GetMousePosition().x;
            }
        }
        break;
    }
    case GameState::Playing: {

        paddle.Update(deltaTime);
        ball.Update(deltaTime);
        // Collision detection
        if (ball.IsCollidingWithPaddle(paddle) && score > scoreLastRound) {
            scoreLastRound = score;
        };
        // Game over
        if (!ball.GetCanMove()) {
            if (scoreLastRound > maxScore) {
                maxScore = scoreLastRound;
            }
            gameState = GameState::BallLost;
        }
        break;
    }
    case GameState::BallLost: {
        if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gameState = GameState::Playing;
            score = 0;
            scoreLastRound = 0;
            ball.Reset();
            paddle.Reset();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                paddle.position.x = GetMousePosition().x;
            }
        }
        break;
    }
    }
    if (GetScreenDimensionChanged()) {
        SetDisplayScale();
        ball.Reset();
        paddle.Reset();
    }
    background.Update(deltaTime);
}

// Render everything
void Game::Draw()
{

    BeginDrawing();
    ClearBackground(BLACK);
    background.Draw();
    switch (gameState) {
    case GameState::Title: {
        DrawTitle();
        break;
    }
    case GameState::Playing: {
        ball.Draw(ballTexture);
        paddle.Draw(paddleTexture);
        DrawScore();
        if (GameSettings::showDebug) {
            DrawRectangleLines(5, 5, GameSettings::screenWidth - 10, GameSettings::screenHeight - 10, RED);
        }
        break;
    }
    case GameState::BallLost: {
        ball.Draw(ballTexture);
        paddle.Draw(paddleTexture);
        DrawBallLost();
        break;
    }
    }

    EndDrawing();
}

// Release resources and close the window
void Game::Quit()
{
    UnloadTexture(ballTexture);
    UnloadTexture(paddleTexture);
    UnloadTexture(cloudTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(titleTexture);
    UnloadSound(bounceSound);
    UnloadSound(hitSound);
    CloseWindow();
}

void Game::DrawTitle()
{
    DrawTextureEx(titleTexture, Vector2 { GetScreenCenter().x - GetScaledTextureDimensions(titleTexture).x / 4, GetScreenCenter().y - GetScaledTextureDimensions(titleTexture).y / 2 }, 0, GameSettings::scaleFactor / 2, WHITE);
    auto pressEnterText = std::string("Press Space to Start ");
    DrawText(pressEnterText.c_str(), GameSettings::screenWidth / 2 - MeasureText(pressEnterText.c_str(), GameSettings::baseFontSize) / 2, GameSettings::screenHeight / 2, GameSettings::baseFontSize, WHITE);
}

void Game::DrawScore()
{
    auto bouncesString = std::string("BOUNCES: ") + std::to_string(score);
    DrawText(bouncesString.c_str(), GameSettings::screenWidth / 2 - MeasureText(bouncesString.c_str(), GameSettings::baseFontSize) / 2, 50, GameSettings::baseFontSize + 4, DARKGRAY);
}

void Game::DrawBallLost()
{
    auto ballLostText = std::string("Ball Lost");
    DrawText(ballLostText.c_str(), GameSettings::screenWidth / 2 - MeasureText(ballLostText.c_str(), GameSettings::baseFontSize) / 2, GameSettings::screenHeight / 2, GameSettings::baseFontSize, WHITE);
    auto maxScore = std::string("Max Score: ") + std::to_string(this->maxScore) + std::string(", bounces this game: ") + std::to_string(scoreLastRound);
    DrawText(maxScore.c_str(), GameSettings::screenWidth / 2 - MeasureText(maxScore.c_str(), GameSettings::baseFontSize) / 2, GameSettings::screenHeight / 2 + GameSettings::baseFontSize, GameSettings::baseFontSize, WHITE);
    auto ballLostText2 = std::string("Press Space to Start Again");
    DrawText(ballLostText2.c_str(), GameSettings::screenWidth / 2 - MeasureText(ballLostText2.c_str(), GameSettings::baseFontSize) / 2, GameSettings::screenHeight / 2 + GameSettings::baseFontSize * 2, GameSettings::baseFontSize, WHITE);
}

// Recalculate the scale factor and base font size, due to window being resized
void Game::SetDisplayScale()
{
    float scale = GameSettings::screenHeight / static_cast<float>(backgroundTexture.height);
    if (GameSettings::scaleFactor != scale) {
        GameSettings::scaleFactor = scale;
    }
    GameSettings::baseFontSize = ceil(GameSettings::screenHeight / 36);
}
