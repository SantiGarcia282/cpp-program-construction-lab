#pragma once
#include "GameState.h"

class InteractionMapper {
public:
    explicit InteractionMapper(int frameWidth);

    GameState update(int markerX);
    void spawnBall();

    const GameState& getState() const { return state_; }

private:
    int frameWidth_;
    GameState state_;

    void positionGlove(float normalizedX);
    void updateBall();
    bool checkSave() const;

    static float clamp01(float v);
};