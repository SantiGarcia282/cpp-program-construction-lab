
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "InteractionMapping.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    const int FRAME_WIDTH = 640;
    InteractionMapper mapper(FRAME_WIDTH);

    std::cout << "=== InteractionMapping standalone test ===\n";
    std::cout << "Simulated marker sweeping across frame.\n\n";

    mapper.spawnBall();

    int step = 0;
    while (true) {
        int phase = step % 80;
        int simulatedMarkerX = (phase < 40)
            ? 100 + phase * 12
            : 580 - (phase - 40) * 12;

        GameState state = mapper.update(simulatedMarkerX);

        
        if (step % 1 == 0) {
            std::cout << "Marker X = " << simulatedMarkerX
                      << "  |  Glove X = " << state.gloveX
                      << "  |  Ball y = " << state.ball.y
                      << "  |  Ball x = " << state.ball.x
                      << "  Active = " << (state.ballActive ? "yes" : "no ")
                      << "  Score = " << state.score;
            if (state.saveMade) std::cout << "  <-- SAVE!";
            std::cout << "\n";
        }

        if (!state.ballActive) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            mapper.spawnBall();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        step++;
    }
    return 0;
}