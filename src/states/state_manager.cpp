#include <iostream>

#include "state_manager.h"

StateManager::StateManager() {};
StateManager::~StateManager() = default;

void StateManager::deInitialize() {
    popStates(states.size() - 1);
    states.back()->deInit();
    states.pop_back();
}

void StateManager::pushState(std::shared_ptr<State> newState) {
    states.push_back(newState);
}

void StateManager::popState() {
    if (states.size() > 1) {
        states.back()->deInit();
        states.pop_back();
        if (states.back()->isReverseInit())
            states.back()->init();
    }
    else
        std::cout << "ERROR! Cannot remove final state\n";
}

void StateManager::popStates(const unsigned int pops) {
    if (pops >= states.size()) {
        std::cout << pops << "ERROR! Cannot pop all or more than loaded states\n";
    }
    else {
        for(size_t i {0}; i < pops; i++) {
            states.back()->deInit();
            states.pop_back();
            if (states.back()->isReverseInit() && i == pops - 1)
                states.back()->init();
        }
    }
}

void StateManager::update(Camera2D& camera2D, Camera3D& camera3D) {
    states.back()->update(camera2D, camera3D);

    bool popCurrentState = states.back()->shouldStatePop();

    if (states.back()->getNextState() != NO_STATE && !popCurrentState) {
        StateType nextState = states.back()->getNextState();
        switch (nextState)
        {
        case LOGO_STATE:
            pushState(std::make_shared<LogoState>());
            break;
        case MENU_STATE:
            pushState(std::make_shared<MenuState>());
            break;
        case PLAY_STATE:
            pushState(std::make_shared<PlayState>());
            break;
        default:
            break;
        }
    }

    if (popCurrentState)
        popState();
}

void StateManager::render(const Camera2D& camera2D, const Camera3D& camera3D) const {
    for (auto iter = states.begin(); iter != states.end(); ++iter) {
        if (iter->get()->shouldStateRender()) {
            StateCam stateCam = iter->get()->getStateDimension();
            switch (stateCam)
            {
            case STATE_NOCAM:
                iter->get()->render(camera2D, camera3D);
                break;
            case STATE_2DCAM:
                BeginMode2D(camera2D);
                    iter->get()->render(camera2D, camera3D);
                EndMode2D();
                break;
            case STATE_3DCAM:
                BeginMode3D(camera3D);
                    iter->get()->render(camera2D, camera3D);
                EndMode3D();
                break;
            default:
                break;
            }
        }
    }
}
