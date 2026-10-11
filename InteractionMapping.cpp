#include "InteractionMapping.h"
#include <algorithm>
#include <cstdlib>

InteractionMapper::InteractionMapper(int frameWidth)
    : frameWidth_(frameWidth > 0 ? frameWidth : 1)
{
    state_.gloveX = 0.5f;
}

float InteractionMapper::clamp01(float v) {
    return std::max(0.0f, std::min(1.0f, v));
}

void InteractionMapper::positionGlove(float normalizedX) {
    state_.gloveX = clamp01(normalizedX);
}

void InteractionMapper::spawnBall() {
    state_.ball.x = 0.2f + (static_cast<float>(std::rand()) / RAND_MAX) * 0.6f; //randomize X
    state_.ball.y = 0.0f;
    state_.ballActive = true;
    state_.saveMade = false;
}

bool InteractionMapper::checkSave() const {
    const float ballHalfWidth  = 0.03f;
    const float gloveHalfWidth = state_.gloveWidth * 0.5f;
    return std::abs(state_.gloveX - state_.ball.x) < (gloveHalfWidth + ballHalfWidth); //check if gloves and ball collide
}

void InteractionMapper::updateBall() {
    if (!state_.ballActive) return;

    state_.ball.y += state_.ball.speed; //simulate ball reaching goal

    if (state_.ball.y >= 0.95f) { // ball will always hit the goal at 0.95 y or above therefore save checked here
        state_.ball.y = 0.95f;
        state_.saveMade = checkSave(); 
        if (state_.saveMade) state_.score += 1;
        state_.ballActive = false;
    }
}

GameState InteractionMapper::update(int markerX) {
    float normalizedX = static_cast<float>(markerX) / static_cast<float>(frameWidth_);
    positionGlove(normalizedX);
    updateBall();
    return state_;
}