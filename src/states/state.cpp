#include "states.h"

void State::PopSelf() {
    popState = true;
}

State::State() = default;
State::~State() = default;

void State::init() {};
void State::deInit() {};

StateType State::getNextState() const {
    return nextState;
}

bool State::shouldStateRender() const {
    return stateRender;
}

StateCam State::getStateDimension() const {
    return stateCam;
}

bool State::isReverseInit() const {
    return reverseInit;
}

bool State::shouldStatePop() const {
    return popState;
}
