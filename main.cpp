#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "InteractionMapping.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int FRAME_WIDTH = 640;
    const int FRAME_HEIGHT = 480;
    
    InteractionMapper mapper(FRAME_WIDTH, FRAME_HEIGHT);

    std::cout << "=== InteractionMapping standalone test ===\n";
    std::cout << "Simulated marker moving in 2D.\n\n";

    mapper.spawnBall();

    int step = 0;
    while (true) {
        //random x and y coords
        int simulatedMarkerX = 320;
        int simulatedMarkerY = 400;

        GameState state = mapper.update(simulatedMarkerX, simulatedMarkerY);

        if (step % 2 == 0) { //print every other step to reduce spam
            std::cout << "Marker(X,Y) = (" << simulatedMarkerX << "," << simulatedMarkerY << ")"
                      << " | Glove(X,Y) = (" << state.gloveX << "," << state.gloveY << ")"
                      << " | Ball(X,Y) = (" << state.ball.x << "," << state.ball.y << ")"
                      << " | Active = " << (state.ballActive ? "yes" : "no ")
                      << " | Score = " << state.score;
            if (state.saveMade) std::cout << "  <-- SAVE!";
            std::cout << "\n";
        }

        if (!state.ballActive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            mapper.spawnBall();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        step++;
    }
    return 0;
}