#ifndef PLAY_STATE_CPP
#define PLAY_STATE_CPP

#include "raylib.h"

#include <sstream>
#include <iomanip>
#include <iostream>

#include "states.hpp"

PlayState::PlayState() {
    init();
}

void PlayState::init() {
    playerSize = {128.0f, 32.0f};
    playerPos = {(float)GetScreenWidth()/2 - playerSize.x/2, (float)GetScreenHeight()/2};// - 128 - playerSize.y};
    playerSpeed = 300.0f;

    ballRadius = 24.0f;
    ballPos = {(float)GetScreenWidth()/2, (float)GetScreenHeight()/3};
    ballSpeed = 200.0f;
    ballDir = {1.0f, 1.0f};

    screenBoundsLeft = 0.0f;
    screenBoundsRight = 500.0f;
    screenBoundsTop = 0.0f;
    screenBoundsBot = 500.0f;

    coinSound = LoadSound("resources/coin.wav");
}

void PlayState::deInit() {
    UnloadSound(coinSound);
}

void PlayState::update(Camera2D& camera2D, Camera3D& camera3D) {
    if (IsKeyPressed(KEY_Q))
        PopSelf();
    
    float width = GetScreenWidth();
    float height = GetScreenHeight();

    camera2D.offset = Vector2{(float)width/2, (float)height/2};
    camera2D.target = Vector2{(float)width/2, (float)height/2};

    if (width > height) {
        camera2D.zoom = (float)height/500;
    }
    else {
        camera2D.zoom = (float)width/500;
    }

    screenBoundsLeft = (GetScreenWidth()/2) - (GetScreenWidth() / (2 * camera2D.zoom));
    screenBoundsRight = (GetScreenWidth()/2) + (GetScreenWidth() / (2 * camera2D.zoom));
    screenBoundsTop = (GetScreenHeight()/2) - (GetScreenHeight() / (2 * camera2D.zoom));
    screenBoundsBot = (GetScreenHeight()/2) + (GetScreenHeight() / (2 * camera2D.zoom));
    
    float playerDirX = 0.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        playerDirX -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        playerDirX += 1.0f;

    playerPos.x += playerDirX * playerSpeed * GetFrameTime();
    playerPos.y = screenBoundsBot - playerSize.y - 64.0f;

    if (playerPos.x < screenBoundsLeft)
        playerPos.x = screenBoundsLeft;
    if (playerPos.x > screenBoundsRight - playerSize.x)
        playerPos.x = screenBoundsRight - playerSize.x;

    ballPos.x += ballDir.x * ballSpeed * GetFrameTime();
    ballPos.y += ballDir.y * ballSpeed * GetFrameTime();

    if (ballPos.x < screenBoundsLeft + ballRadius) {
        ballPos.x = screenBoundsLeft + ballRadius;
        ballDir.x = -ballDir.x;
    }
    if (ballPos.x > screenBoundsRight - ballRadius) {
        ballPos.x = screenBoundsRight - ballRadius;
        ballDir.x = -ballDir.x;
    }
    if (ballPos.y < screenBoundsTop + ballRadius) {
        ballPos.y = screenBoundsTop + ballRadius;
        ballDir.y = -ballDir.y;
    }
    if (ballPos.y > screenBoundsBot - ballRadius) {
        ballPos.x = GetScreenWidth()/2;
        ballPos.y = GetScreenHeight()/3;
    }

    if (CheckCollisionCircleRec(ballPos, ballRadius, {playerPos.x, playerPos.y, playerSize.x, playerSize.y})) {
        ballPos.y = playerPos.y - ballRadius;
        ballDir.y = -ballDir.y;

        PlaySound(coinSound);
    }
}

void PlayState::render(const Camera2D& camera2D, const Camera3D& camera3D) {
    Vector2 textPos = GetScreenToWorld2D({20,20}, camera2D);
    DrawText("Press Q to exit to main menu", textPos.x, textPos.y, 32, BLACK);
    DrawRectangleV(playerPos, playerSize, RED);
    DrawCircleV(ballPos, ballRadius, BLUE);
}

#endif