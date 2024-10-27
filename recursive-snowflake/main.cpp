#include <math.h>

#include "raylib.h"

void drawPentagonBranches(float centerX, float centerY, float radius, float baseAngle, float length, int depth, const Color &color = WHITE)
{
  if (depth == 0)
    return;
  // Draw five branches from pentagon points
  for (int i = 0; i < 5; i++)
  {
    float angle = baseAngle + (i * 2 * PI / 5);
    float x = centerX + radius * cosf(angle);
    float y = centerY + radius * sinf(angle);
    // Draw line from center to pentagon point
    DrawLine(centerX, centerY, x, y, color);
    // Create new pentagon at the end of each line
    if (depth > 0)
    {
      float newRadius = radius * 0.4f;  // Smaller pentagon
      drawPentagonBranches(x, y, newRadius, angle, length * 0.4f, depth - 1, color);
    }
  }
}

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  int currentDepth = 1;
  const int maxDepth = 10;  // Reduced max depth since pattern grows exponentially

  InitWindow(screenWidth, screenHeight, "Recursive Pentagon Snowflake");
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

    // Draw initial pentagon and its branches
    float centerX = (float)screenWidth / 2;
    float centerY = (float)screenHeight / 2;
    float initialRadius = 100.0f;
    float baseLength = 60.0f;

    // Start with pentagon pointing up (-PI/2)
    drawPentagonBranches(centerX, centerY, initialRadius, -PI / 2, baseLength, currentDepth, BLUE);

    // Draw instructions
    DrawText("Use UP/DOWN arrows to change recursion depth", 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Current Depth: %d", currentDepth), 10, 40, 20, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
