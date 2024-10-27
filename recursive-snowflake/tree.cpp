#include <math.h>

#include "raylib.h"

void drawRecursiveLines(float x, float y, float length, float angle, int depth)
{
  if (depth == 0)
    return;

  // Draw main line
  float endX = x + length * cosf(angle);
  float endY = y + length * sinf(angle);
  DrawLine(x, y, endX, endY, WHITE);

  // Calculate new length for branches
  float newLength = length * 0.5f;

  // Draw left branch
  drawRecursiveLines(endX, endY, newLength, angle - 0.6f, depth - 1);

  // Draw forward (center) branch - slightly longer
  drawRecursiveLines(endX, endY, newLength * 1.2f, angle, depth - 1);

  // Draw right branch
  drawRecursiveLines(endX, endY, newLength, angle + 0.6f, depth - 1);
}

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  int currentDepth = 1;
  const int maxDepth = 6;

  InitWindow(screenWidth, screenHeight, "Recursive Lines");
  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    // Update
    if (IsKeyPressed(KEY_UP) && currentDepth < maxDepth)
      currentDepth++;
    if (IsKeyPressed(KEY_DOWN) && currentDepth > 0)
      currentDepth--;

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw three main branches from bottom center
    float startX = screenWidth / 2;
    float startY = screenHeight - 100;
    float baseLength = 120.0f;

    // Left branch
    drawRecursiveLines(startX, startY, baseLength, -2.8f, currentDepth);
    // Center branch
    drawRecursiveLines(startX, startY, baseLength, -PI / 2, currentDepth);
    // Right branch
    drawRecursiveLines(startX, startY, baseLength, -0.3f, currentDepth);

    // Draw instructions
    DrawText("Use UP/DOWN arrows to change recursion depth", 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Current Depth: %d", currentDepth), 10, 40, 20, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
