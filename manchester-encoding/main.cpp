#include <vector>

#include "raylib.h"

const int orgY = 180;
const Color upTransitionColor = {255, 0, 0, 255};
const Color downTransitionColor = {0, 255, 0, 255};
const int clock_period = 80;
const std::vector<int> bits_data = {1, 0, 1, 1, 0, 0, 1, 0};
const int amp = 60;

void DrawArrow(int x, int y1, int y2, int amplitude, Color color)
{
  int arrowSize = 20;                  // Arrowhead size
  int direction = (y2 > y1) ? 1 : -1;  // 1 for down, -1 for up

  // Draw the main line first
  DrawLine(x, y1, x, y2, color);

  // Calculate the arrowhead points
  int arrowTipY = y2;                      // The tip of the arrow is at the end of the line (y2)
  int baseY = y2 - direction * arrowSize;  // The base of the arrowhead
  int leftX = x - arrowSize / 2;           // Left point of the arrowhead
  int rightX = x + arrowSize / 2;          // Right point of the arrowhead

  // Draw arrowhead using lines
  if (direction == 1)
  {                                                // Downward arrow
    DrawLine(x, arrowTipY, leftX, baseY, color);   // Left side of the arrow
    DrawLine(x, arrowTipY, rightX, baseY, color);  // Right side of the arrow
    DrawLine(leftX, baseY, rightX, baseY, color);  // Base of the arrow
  }
  else
  {                                                                                // Upward arrow
    DrawLine(x, arrowTipY, leftX, arrowTipY + arrowSize, color);                   // Left side of the arrow
    DrawLine(x, arrowTipY, rightX, arrowTipY + arrowSize, color);                  // Right side of the arrow
    DrawLine(leftX, arrowTipY + arrowSize, rightX, arrowTipY + arrowSize, color);  // Base of the arrow
  }
}

class ManchesterVisualizer
{
private:
  std::vector<int> bits;
  int clockPeriod;
  int amplitude;
  int baseline;

public:
  ManchesterVisualizer() : clockPeriod(clock_period), amplitude(amp), baseline(0), bits(bits_data) {}  // Example bit pattern

  void setBit(int index, int value)
  {
    if (index >= 0 && index < bits.size())
      bits[index] = value;
  }

  void draw(int startX, int startY, const char *label)
  {
    // Draw label
    DrawText(label, startX, startY - amplitude - 30, 20, WHITE);
    int factor = 50;
    int signalY = startY + factor;

    // Draw baseline
    DrawLine(startX, signalY, startX + bits.size() * clockPeriod, signalY, GRAY);

    // Draw vertical time markers and bit numbers
    for (int i = 0; i <= bits.size(); i++)
    {
      int x = startX + i * clockPeriod;
      DrawLine(x, signalY - amplitude - 10, x, startY + amplitude + 10, DARKGRAY);
      if (i < bits.size())
        DrawText(TextFormat("%d", bits[i]), x + clockPeriod / 3, signalY - amplitude - 20, 20, GRAY);
    }

    // Draw original digital signal
    int lastY = startY - (bits[0] * amplitude);
    for (int i = 0; i < bits.size(); i++)
    {
      int x1 = startX + i * clockPeriod;
      int x2 = startX + (i + 1) * clockPeriod;
      int y = signalY - (bits[i] * amplitude);

      // Draw horizontal line for bit value
      DrawLine(x1, y, x2, y, WHITE);

      // Draw vertical line connecting to next bit
      if (i < bits.size() - 1)
      {
        int nextY = signalY - (bits[i + 1] * amplitude);
        DrawLine(x2, y, x2, nextY, WHITE);
      }
    }
  }

  void drawManchester(int startX, int startY)
  {
    // Draw baseline
    DrawLine(startX, startY, startX + bits.size() * clockPeriod, startY, GRAY);

    // Draw Manchester encoded signal
    for (int i = 0; i < bits.size(); i++)
    {
      int x1 = startX + i * clockPeriod;
      int xMid = x1 + clockPeriod / 2;
      int x2 = x1 + clockPeriod;

      if (bits[i] == 1)
      {
        // For 1: High-to-Low transition
        DrawLine(x1, startY - amplitude, xMid, startY - amplitude, WHITE);
        // DrawLine(xMid, startY - amplitude, xMid, startY + amplitude, WHITE);
        DrawArrow(xMid, startY - amplitude, startY + amplitude, amplitude, downTransitionColor);
        DrawLine(xMid, startY + amplitude, x2, startY + amplitude, WHITE);
      }
      else
      {
        // For 0: Low-to-High transition
        DrawLine(x1, startY + amplitude, xMid, startY + amplitude, WHITE);
        // DrawLine(xMid, startY + amplitude, xMid, startY - amplitude, WHITE);
        DrawArrow(xMid, startY + amplitude, startY - amplitude, amplitude, upTransitionColor);
        DrawLine(xMid, startY - amplitude, x2, startY - amplitude, WHITE);
      }
    }
  }

  void drawDifferentialManchester(int startX, int startY)
  {
    // Draw baseline
    DrawLine(startX, startY, startX + bits.size() * clockPeriod, startY, GRAY);

    // Track the current level (high or low)
    bool currentLevel = false;  // Start from low

    for (int i = 0; i < bits.size(); i++)
    {
      int x1 = startX + i * clockPeriod;  // Start of the pulse
      int xMid = x1 + clockPeriod / 2;    // Midpoint of the pulse
      int x2 = x1 + clockPeriod;          // End of the pulse

      if (bits[i] == 1)
      {
        // Bit 1: No transition at start, transition in the middle
        DrawLine(x1,
                 startY + (currentLevel ? -amplitude : amplitude),
                 xMid,
                 startY + (currentLevel ? -amplitude : amplitude),
                 GREEN);  // Draw horizontal line for bit 1

        // Transition to the opposite level at mid

        DrawLine(xMid,
                 startY + (currentLevel ? -amplitude : amplitude),
                 xMid,
                 startY + (currentLevel ? amplitude : -amplitude),
                 GREEN);  // Vertical transition for bit 1

        // Draw horizontal line at new level to end of pulse
        DrawLine(xMid,
                 startY + (currentLevel ? amplitude : -amplitude),
                 x2,
                 startY + (currentLevel ? amplitude : -amplitude),
                 GREEN);  // Draw horizontal line to end for bit 1
        currentLevel = !currentLevel;
      }
      else
      {
        // Draw horizontal line at new level to midpoint
        DrawLine(x1,
                 startY + (currentLevel ? amplitude : -amplitude),
                 xMid,
                 startY + (currentLevel ? amplitude : -amplitude),
                 RED);  // Draw horizontal line for bit 0

        DrawLine(xMid,
                 startY + (currentLevel ? amplitude : -amplitude),
                 xMid,
                 startY + (currentLevel ? -amplitude : amplitude),
                 RED);  // Vertical transition back to original level

        // Draw horizontal line at new level to end of pulse
        DrawLine(xMid,
                 startY + (currentLevel ? -amplitude : amplitude),
                 x2,
                 startY + (currentLevel ? -amplitude : amplitude),
                 RED);  // Draw horizontal line to end for bit 0
      }
    }
  }

  void update()
  {
    // Toggle bit value when mouse clicks on a bit position
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      Vector2 mouse = GetMousePosition();
      for (int i = 0; i < bits.size(); i++)
      {
        int x = 50 + i * clockPeriod;
        if (mouse.x >= x && mouse.x < x + clockPeriod && mouse.y >= orgY - amplitude && mouse.y <= orgY + amplitude)
        {
          bits[i] = !bits[i];
          break;
        }
      }
    }
  }

  void DrawReferenceLines(int startX, int startY, int numberOfBits, int clockPeriod)
  {
    for (int i = 1; i <= numberOfBits; i++)
    {
      int x = startX + i * clockPeriod;
      DrawLine(x, startY - 10, x, 600, {200, 200, 200, 80});  // Vertical line
      if (i < numberOfBits)
      {
        // Optional: Draw text labels for the time markers
        DrawText(TextFormat("%d", i), x - 5, startY + 60, 20, WHITE);
      }
    }
  }
};

int main()
{
  InitWindow(800, 800, "Manchester Encoding Visualization");
  SetTargetFPS(60);

  ManchesterVisualizer visualizer;

  while (!WindowShouldClose())
  {
    visualizer.update();

    BeginDrawing();
    ClearBackground(BLACK);

    visualizer.DrawReferenceLines(50, orgY, bits_data.size(), clock_period);
    // Draw original and Manchester encoded signals
    visualizer.draw(50, orgY, "Original Signal [Click on the original signal to toggle bits]");
    visualizer.drawManchester(50, 400);
    DrawText("Manchester Encoded", 50, 300, 20, WHITE);
    DrawText("Differential Manchester", 50, 500, 20, WHITE);
    visualizer.drawDifferentialManchester(50, 600);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
