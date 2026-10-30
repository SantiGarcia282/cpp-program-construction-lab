#pragma once

struct Ball {
    float x = 0.5f;
    float y = 0.0f;
    float speedX = 0.0f; //horizontal speed
    float speedY = 0.02f; //vertical speed 
};

struct GameState {
    float gloveX = 0.5f;      
    float gloveY = 0.9f;      
    float gloveWidth = 0.15f; 
    float gloveHeight = 0.15f;

    Ball ball;
    int score = 0;
    bool ballActive = false;
    bool saveMade = false;
};