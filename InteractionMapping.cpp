#include "InteractionMapping.h"
#include <algorithm>
#include <cstdlib>

InteractionMapper::InteractionMapper(int frameWidth, int frameHeight) //constructor
    : frameWidth_(frameWidth > 0 ? frameWidth : 1),
      frameHeight_(frameHeight > 0 ? frameHeight : 1)
{
    state_.gloveX = 0.5f;
    state_.gloveY = 0.9f; 
}

float InteractionMapper::clamp01(float v) {
    return std::max(0.0f, std::min(1.0f, v));
}

void InteractionMapper::positionGlove(float normalizedX, float normalizedY) {
    state_.gloveX = clamp01(normalizedX); //clamp so gloves can leave screen
    state_.gloveY = clamp01(normalizedY);
}

void InteractionMapper::spawnBall() {
    state_.ball.x = 0.2f + (static_cast<float>(std::rand()) / RAND_MAX) * 0.6f;
    state_.ball.y = 0.0f;
    
    //Ball moves towards the center goal area
    state_.ball.speedX = (0.5f - state_.ball.x) * 0.01f; //move towards center X
    state_.ball.speedY = 0.02f; // shoots up
    
    state_.ballActive = true;
    state_.saveMade = false;
}

bool InteractionMapper::checkSave() const {
    //distance between ball center and glove center
    float dx = std::abs(state_.gloveX - state_.ball.x);
    float dy = std::abs(state_.gloveY - state_.ball.y);

    bool overlapX = dx < (state_.gloveWidth * 0.5f + 0.03f);
    bool overlapY = dy < (state_.gloveHeight * 0.5f + 0.03f);

    return overlapX && overlapY;
}

void InteractionMapper::updateBall() {
    if (!state_.ballActive) return;

    //moving the ball
    state_.ball.x += state_.ball.speedX;
    state_.ball.y += state_.ball.speedY;

    //check for save if ball is above 0.85
    if (state_.ball.y >= 0.85f) {
        state_.saveMade = checkSave();
        if (state_.saveMade) state_.score += 1;
        state_.ballActive = false; //ball is removed
    }
}

GameState InteractionMapper::update(int markerX, int markerY) {
    float normalizedX = static_cast<float>(markerX) / static_cast<float>(frameWidth_);
    float normalizedY = static_cast<float>(markerY) / static_cast<float>(frameHeight_);
    
    positionGlove(normalizedX, normalizedY);
    updateBall();
    return state_;
}