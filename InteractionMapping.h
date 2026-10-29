#pragma once
#include "GameState.h"

class InteractionMapper {
public:
    explicit InteractionMapper(int frameWidth, int frameHeight);

    GameState update(int markerX, int markerY);
    void spawnBall();

    const GameState& getState() const { return state_; }

private:
    int frameWidth_;
    int frameHeight_; 
    GameState state_;

    void positionGlove(float normalizedX, float normalizedY);
    void updateBall();
    bool checkSave() const;

    static float clamp01(float v);
};