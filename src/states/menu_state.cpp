#ifndef MENU_STATE_CPP
#define MENU_STATE_CPP

#include "raylib.h"

#include "states.hpp"
#include "../exiter.hpp"

MenuState::MenuState() {
    init();
}

void MenuState::init() {
    reverseInit = true;
    nextState = NO_STATE;
    stateCam = STATE_NOCAM;
    stateRender = true;

    logoPosition = {(float)GetScreenWidth()/2 - 192, 64.0f};

    buttonsLeftTop = {(float)GetScreenWidth()/2 - 128, 224.0f};

    logoSize = {384.0f, 128.0f};

    buttonSize = {256.0f, 64.0f};
    buttonSpacing = 24.0f;

    buttonCount = 3;

    if (!IsFontValid(font))
        font = LoadFont("resources/mecha.png");
    fontSize = 48;

    quitGame = false;
}

void MenuState::deInit() {
    /*  -----------------------------------------------------------------------------------------------------
        window close seems to handle this, and if you do it yourself it tries to double free default font.
        not sure what exactly is the best way to handle this as it feels wrong to not unload the font myself,
        like what if I have multiple fonts?  
    */
    // if (IsFontValid(font))
        // UnloadFont(font);
}

void MenuState::update(Camera2D& camera2D, Camera3D& camera3D) {
    if (quitGame) {
        deInit();
        Exiter::Get().CloseGame();
        stateRender = false;
    }
    logoPosition = {(float)GetScreenWidth()/2 - 192, 64.0f};

    buttonsLeftTop = {(float)GetScreenWidth()/2 - 128, 224.0f};
}

void MenuState::render(const Camera2D& camera2D, const Camera3D& camera3D) {
    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_SIZE, fontSize);
    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

    GuiLabel({logoPosition.x, logoPosition.y, logoSize.x, logoSize.y}, "Raylib Game Template");

    bool playGame = GuiButton({buttonsLeftTop.x, buttonsLeftTop.y, buttonSize.x, buttonSize.y}, "Play");

    bool openOptions = GuiButton({buttonsLeftTop.x, buttonsLeftTop.y + buttonSize.y + buttonSpacing, buttonSize.x, buttonSize.y}, "Options");

#if !defined(PLATFORM_WEB)
    quitGame = GuiButton({buttonsLeftTop.x, buttonsLeftTop.y + ((buttonSize.y + buttonSpacing) * 2), buttonSize.x, buttonSize.y}, "Quit");
#endif
    if (playGame) {
        nextState = PLAY_STATE;
        stateRender = false;
    }
    if (openOptions) {

    }
}

#endif