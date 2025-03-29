#include "raylib.h"
#include <cmath>
#include <vector>
#include <string>

// Constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define DEFAULT_SLIT_DISTANCE 50
#define DEFAULT_WAVELENGTH 20
#define SOURCE_Y 100
#define INTENSITY_SCALE 255
#define BUFFER_SIZE 200

struct WaveSource
{
  Vector2 position;
};

// Pre-render to a texture for performance
RenderTexture2D simulationTexture;
float currentTime = 0.0f;
int slitDistance = DEFAULT_SLIT_DISTANCE;
int wavelength = DEFAULT_WAVELENGTH;
bool animateWaves = true;
bool showControls = true;
bool useColorMode = true;
int sourceCount = 2;  // Default is double-slit

// Render the simulation to a texture
void RenderSimulation(std::vector<WaveSource> &sources, float time)
{
  BeginTextureMode(simulationTexture);
  ClearBackground(BLACK);

  // Calculate only pixels below the sources
  for (int y = SOURCE_Y; y < SCREEN_HEIGHT; y++)
  {
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      float intensity = 0.0f;

      for (const auto &source : sources)
      {
        float dx = x - source.position.x;
        float dy = y - source.position.y;
        float distance = sqrt(dx * dx + dy * dy);

        // Add time component for animation
        if (animateWaves)
          intensity += sinf(2 * PI * (distance / wavelength - time));
        else
          intensity += sinf(2 * PI * distance / wavelength);
      }

      // Normalize to [0,1]
      intensity = (intensity / sources.size() + 1) / 2;

      Color color;
      if (useColorMode)
      {
        // Rainbow effect based on phase
        float hue = fmodf(intensity * 360, 360);
        color = ColorFromHSV(hue, 0.8f, intensity);
      }
      else
      {
        // Grayscale
        unsigned char brightness = (unsigned char)(intensity * INTENSITY_SCALE);
        color = {brightness, brightness, brightness, 255};
      }

      DrawPixel(x, y, color);
    }
  }

  // Draw the slits as bright points
  for (const auto &source : sources) DrawCircle(source.position.x, source.position.y, 2, WHITE);

  EndTextureMode();
}

// Update the position of wave sources
void UpdateSources(std::vector<WaveSource> &sources, int count, int distance)
{
  sources.clear();

  if (count == 1)
  {
    // Single source in the middle
    sources.push_back({(Vector2){SCREEN_WIDTH / 2, SOURCE_Y}});
  }
  else
  {
    // Calculate spacing for multiple sources
    float totalWidth = distance * (count - 1);
    float startX = SCREEN_WIDTH / 2 - totalWidth / 2;

    for (int i = 0; i < count; i++) sources.push_back({(Vector2){startX + i * distance, SOURCE_Y}});
  }
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Interactive Double-Slit Experiment");
  SetTargetFPS(60);

  // Create a render texture to improve performance
  simulationTexture = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

  // Create initial wave sources
  std::vector<WaveSource> sources;
  UpdateSources(sources, sourceCount, slitDistance);

  // Initial simulation render
  RenderSimulation(sources, currentTime);

  // Text buffer for instructions
  char textBuffer[BUFFER_SIZE];

  while (!WindowShouldClose())
  {
    // Update
    float deltaTime = GetFrameTime();
    bool shouldRerender = false;

    // Wave animation
    if (animateWaves)
    {
      currentTime += deltaTime * 0.5f;
      shouldRerender = true;
    }

    // Toggle controls display
    if (IsKeyPressed(KEY_H)) showControls = !showControls;

    // Toggle color mode
    if (IsKeyPressed(KEY_C))
    {
      useColorMode = !useColorMode;
      shouldRerender = true;
    }

    // Toggle animation
    if (IsKeyPressed(KEY_A)) animateWaves = !animateWaves;

    // Adjust wavelength
    if (IsKeyDown(KEY_UP))
    {
      wavelength = wavelength + 1;
      shouldRerender = true;
    }
    if (IsKeyDown(KEY_DOWN) && wavelength > 5)
    {
      wavelength = wavelength - 1;
      shouldRerender = true;
    }

    // Adjust slit distance
    if (IsKeyDown(KEY_RIGHT))
    {
      slitDistance = slitDistance + 1;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyDown(KEY_LEFT) && slitDistance > 10)
    {
      slitDistance = slitDistance - 1;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }

    // Change number of slits
    if (IsKeyPressed(KEY_ONE) && sourceCount != 1)
    {
      sourceCount = 1;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyPressed(KEY_TWO) && sourceCount != 2)
    {
      sourceCount = 2;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyPressed(KEY_THREE) && sourceCount != 3)
    {
      sourceCount = 3;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyPressed(KEY_FOUR) && sourceCount != 4)
    {
      sourceCount = 4;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyPressed(KEY_FIVE) && sourceCount != 5)
    {
      sourceCount = 5;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }
    if (IsKeyPressed(KEY_SIX) && sourceCount != 6)
    {
      sourceCount = 6;
      UpdateSources(sources, sourceCount, slitDistance);
      shouldRerender = true;
    }

    // Re-render the simulation texture if needed
    if (shouldRerender) RenderSimulation(sources, currentTime);

    // Drawing
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw simulation texture
    DrawTextureRec(simulationTexture.texture,
                   (Rectangle){0, 0, (float)simulationTexture.texture.width, (float)-simulationTexture.texture.height}, (Vector2){0, 0},
                   WHITE);

    // Draw barrier
    DrawRectangle(0, SOURCE_Y - 10, SCREEN_WIDTH, 10, DARKGRAY);

    // Draw controls and information if enabled
    if (showControls)
    {
      DrawRectangle(0, 0, SCREEN_WIDTH, 95, (Color){0, 0, 0, 180});

      DrawText("Interactive Young's Experiment", 10, 10, 20, WHITE);

      snprintf(textBuffer, BUFFER_SIZE, "Controls: H-Hide Controls | A-Toggle Animation | C-Toggle Colors");
      DrawText(textBuffer, 10, 35, 10, LIGHTGRAY);

      snprintf(textBuffer, BUFFER_SIZE, "UP/DOWN-Adjust Wavelength (%d) | LEFT/RIGHT-Adjust Slit Distance (%d)", wavelength, slitDistance);
      DrawText(textBuffer, 10, 50, 10, LIGHTGRAY);

      snprintf(textBuffer, BUFFER_SIZE, "1-5 Keys: Change Number of Slits (Current: %d)", sourceCount);
      DrawText(textBuffer, 10, 65, 10, LIGHTGRAY);

      snprintf(textBuffer, BUFFER_SIZE, "Mode: %s | Animation: %s", useColorMode ? "Color" : "Grayscale", animateWaves ? "ON" : "OFF");
      DrawText(textBuffer, 10, 80, 10, LIGHTGRAY);
    }
    else { DrawText("Press H to show controls", 10, 10, 10, GRAY); }

    EndDrawing();
  }

  // Clean up
  UnloadRenderTexture(simulationTexture);
  CloseWindow();

  return 0;
}
