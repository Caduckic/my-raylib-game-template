#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"

#include <iostream>

#include "states/state_manager.hpp"

class Game {
private:
    StateManager stateManager;
    Camera2D camera2D;
    Camera3D camera3D;
public:
    Game(const int screenWidth = 800, const int screenHeight = 450) {
        InitWindow(screenWidth, screenHeight, "raylib game template");
        SetWindowState(FLAG_WINDOW_RESIZABLE);

        InitAudioDevice();

        stateManager = {};
        stateManager.pushState(std::make_shared<LogoState>());

        camera2D.offset = Vector2{(float)screenWidth/2, (float)screenHeight/2};
        camera2D.target = Vector2{(float)screenWidth/2, (float)screenHeight/2};
        camera2D.zoom = (float)screenHeight/500;
        camera2D.rotation = 0.0f;

        camera3D.fovy = 45.0f;
        camera3D.position = Vector3{0.0f, 0.0f, 0.0f};
        camera3D.projection = CAMERA_PERSPECTIVE;
        camera3D.target = Vector3{0.0f, 0.0f, -1.0f};
        camera3D.up = Vector3{0.0f, 1.0f, 0.0f};
    }

    ~Game() = default;

    void deInitialize() {
        stateManager.deInitialize();
        CloseAudioDevice();
        CloseWindow();
    }

    void setGameFPS(const int fps) {
        SetTargetFPS(fps);
    }

    void update() {
        stateManager.update(camera2D, camera3D);
    }

    void render() const {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            stateManager.render(camera2D, camera3D);

        EndDrawing();
    }
};

#endif