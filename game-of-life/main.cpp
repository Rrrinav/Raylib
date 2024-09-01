#include "Simulation.hpp"
#include <iostream>
#include <raylib.h>

int main() {

  const int WINDOW_HEIGHT = 750;
  const int WINDOW_WIDTH = 750;
  int FPS = 8;
  const int CELL_SIZE = 10;
  gol game(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);

  std::cout << GetRandomValue(0, 1);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game of Life");
  SetTargetFPS(12);

  // Simulation Loop
  while (!WindowShouldClose()) {
    // Event Handling

    // Update
    game.update();
    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);
    game.Draw();
    EndDrawing();
  }
  CloseWindow();
}
