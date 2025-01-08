#ifndef STATES_H
#define STATES_H

#include "raylib.h"

enum StateType {
    NO_STATE = 0,
    LOGO_STATE,
    MENU_STATE,
    PLAY_STATE
};

enum StateCam {
    STATE_NOCAM = 0,
    STATE_2DCAM,
    STATE_3DCAM
};

class State {
protected:
    StateType nextState = NO_STATE;
    bool stateRender = true;
    StateCam stateCam = STATE_2DCAM;
    bool reverseInit = false;
    bool popState = false;

    void PopSelf();
public:
    State();
    ~State();

    virtual void init();
    virtual void deInit();
    virtual void update(Camera2D& camera2D, Camera3D& camera3D) = 0;
    virtual void render(const Camera2D& camera2D, const Camera3D& camera3D) = 0;
    
    StateType getNextState() const;

    bool shouldStateRender() const;

    StateCam getStateDimension() const;

    bool isReverseInit() const;

    bool shouldStatePop() const;
};

class LogoState : public State {
private:
    int framesCounter;

    float logoPositionX;
    float logoPositionY;

    int lettersCount;

    float topSideRecWidth;
    float leftSideRecHeight;

    float bottomSideRecWidth;
    float rightSideRecHeight;

    int state = 0;
    float alpha = 1.0f;
public:
    LogoState();

    ~LogoState();

    virtual void update(Camera2D& camera2D, Camera3D& camera3D) override;

    virtual void render(const Camera2D& camera2D, const Camera3D& camera3D) override;
};

class MenuState : public State {
private:
    Vector2 logoPosition;
    Vector2 logoSize;

    Vector2 buttonsLeftTop;

    Vector2 buttonSize;
    float buttonSpacing;
    
    int buttonCount;

    Font font;
    int fontSize;

    bool quitGame;
public:
    MenuState();
    ~MenuState();

    virtual void init() override;

    virtual void deInit() override;

    virtual void update(Camera2D& camera2D, Camera3D& camera3D) override;

    virtual void render(const Camera2D& camera2D, const Camera3D& camera3D) override;
};

class PlayState : public State {
private:
    Vector2 playerSize;
    Vector2 playerPos;
    float playerSpeed;

    float ballRadius;
    Vector2 ballPos;
    float ballSpeed;
    Vector2 ballDir;

    float screenBoundsLeft;
    float screenBoundsRight;
    float screenBoundsTop;
    float screenBoundsBot;

    Sound coinSound;
public:
    PlayState();
    ~PlayState();

    virtual void init() override;

    virtual void deInit() override;

    virtual void update(Camera2D& camera2D, Camera3D& camera3D) override;

    virtual void render(const Camera2D& camera2D, const Camera3D& camera3D) override;
};

#endif