#pragma once

struct Ball {
    float x = 0.5f;
    float y = 0.0f;
    float speed = 0.02f;
};

struct GameState {
    float gloveX = 0.5f;      // normalized [0,1], 0 = left, 1 = right
    float gloveWidth = 0.15f; // normalized glove half-hitbox

    Ball ball;
    int score = 0;
    bool ballActive = false;
    bool saveMade = false;
};