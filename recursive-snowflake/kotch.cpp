#include <math.h>

#include "raylib.h"

// Function to draw a Koch line segment recursively
void drawKochLine(float x1, float y1, float x2, float y2, int depth)
{
  if (depth == 0)
  {
    DrawLine((int)x1, (int)y1, (int)x2, (int)y2, WHITE);
    return;
  }

  float dx = x2 - x1;
  float dy = y2 - y1;

  // Calculate the length of the line segment
  float length = sqrt(dx * dx + dy * dy);

  // Calculate points that divide the line into thirds
  float x3 = x1 + dx / 3;
  float y3 = y1 + dy / 3;
  float x4 = x1 + dx * 2 / 3;
  float y4 = y1 + dy * 2 / 3;

  // Calculate the point that forms the peak of the triangle
  float angle = atan2(dy, dx);
  float x5 = x3 + length / 3 * cos(angle - PI / 3);
  float y5 = y3 + length / 3 * sin(angle - PI / 3);

  // Recursively draw the four segments
  drawKochLine(x1, y1, x3, y3, depth - 1);
  drawKochLine(x3, y3, x5, y5, depth - 1);
  drawKochLine(x5, y5, x4, y4, depth - 1);
  drawKochLine(x4, y4, x2, y2, depth - 1);
}

// Function to draw the complete Koch snowflake
void drawKochSnowflake(float centerX, float centerY, float size, int depth)
{
  // Calculate vertices of the equilateral triangle
  float height = size * sqrt(3) / 2;

  float x1 = centerX - size / 2;
  float y1 = centerY + height / 3;

  float x2 = centerX + size / 2;
  float y2 = centerY + height / 3;

  float x3 = centerX;
  float y3 = centerY - 2 * height / 3;

  // Draw three Koch lines to form the snowflake
  drawKochLine(x1, y1, x2, y2, depth);
  drawKochLine(x2, y2, x3, y3, depth);
  drawKochLine(x3, y3, x1, y1, depth);
}

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  int currentDepth = 0;
  const int maxDepth = 10;

  InitWindow(screenWidth, screenHeight, "Koch Snowflake");
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

    // Draw the snowflake
    drawKochSnowflake(screenWidth / 2, screenHeight / 2, 300, currentDepth);

    // Draw instructions
    DrawText("Use UP/DOWN arrows to change recursion depth", 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Current Depth: %d", currentDepth), 10, 40, 20, RAYWHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
