#include "./background.hpp"

void Background::Init(Texture2D& bgTex, Texture2D& cloudTex)
{
    this->backgroundTexture = &bgTex;
    this->cloudTexture = &cloudTex;

    // Calculate the number of clouds needed to fill the screen
    int cloudCount = static_cast<int>(ceil(GetScreenDimension().x / (GetScaledTextureDimensions(*backgroundTexture).x)) * 3);

    // Initialize the clouds
    for (size_t i = 0; i <= cloudCount; i++) {
        auto cloudPosX = static_cast<float>(i * GetRandomValue(0, GameSettings::screenWidth / 3));
        clouds.push_back({ cloudPosX, static_cast<float>(GetRandomValue(0, GameSettings::screenHeight / 4 - GetScaledTextureDimensions(*cloudTexture).y)) });
    }
}

void Background::Update(float deltaTime)
{
    for (auto& cloud : clouds) {
        cloud.x -= 20 * deltaTime;
        if (cloud.x + GetScaledTextureDimensions(*cloudTexture).x < 0) {
            cloud.x = GetScreenDimension().x + GetScaledTextureDimensions(*cloudTexture).x;
            cloud.y = static_cast<float>(GetRandomValue(0, GameSettings::screenHeight / 4 - GetScaledTextureDimensions(*cloudTexture).y));
        }
        cloud.y += (sin(cloud.x / 100) * 3) * deltaTime;
    }
}

void Background::Draw()
{
    if (!backgroundTexture || !cloudTexture) {
        return;
    }

    // Calculate the size of the texture to fit the screen height
    float textureHeight = GetScreenDimension().y;
    float textureWidth = textureHeight * (static_cast<float>(backgroundTexture->width) / static_cast<float>(backgroundTexture->height));
    // Calculate the number of times the texture should repeat horizontally
    int repeatCount = static_cast<int>(ceil(GetScreenDimension().x / textureWidth));

    for (size_t i = 0; i < repeatCount; i++) {
        DrawTexturePro(*backgroundTexture, { 0, 0, static_cast<float>(backgroundTexture->width), static_cast<float>(backgroundTexture->height) }, { textureWidth * i, 0, textureWidth, textureHeight }, { 0, 0 }, 0, Color { 255, 255, 255, 255 });
    }

    for (auto& cloud : clouds) {
        DrawTextureEx(*cloudTexture, cloud, 0, GameSettings::scaleFactor, WHITE);
    }
}
