#include "raylib.h"
#include <chrono>
#include <cstddef>
#include <iostream>
#include <random>

#define HEIGHT 600
#define WIDTH 800

struct Ball {
  float x, y;
  float speedx, speedy;
  float radius;

  Ball(float x, float y, float r, float sx, float sy) {
    this->x = x;
    this->y = y;
    radius = r;
    speedx = sx;
    speedy = sy;
  }

  void Draw(void) {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
    return;
  }
};

struct Racket {
  float x, y;
  float speed;
  size_t width;
  size_t height;

  Racket(float x, float y, int width, int height, float speed) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->speed = speed;
  }

  void Draw() { DrawRectangleRec(get_rect(), GREEN); }

  Rectangle get_rect() {
    return Rectangle{(x - width / 2), (y - height / 2), (float)width,
                     (float)height};
  }
};

const char *winner_text = nullptr;

int getRandomNumber() {
  srand(static_cast<unsigned int>(time(0)));
  int randomNumber =
      rand() * 1000 % 2; // Generate a random number between 0 and 1
  if (randomNumber == 0)
    return 1;
  else
    return -1;
}

int main() {
  InitWindow(WIDTH, HEIGHT, "Pong");
  SetWindowState(FLAG_VSYNC_HINT);

  size_t racket_height = 100;
  size_t racket_width = 10;

  Ball ball(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 15, 300, 300);

  Racket racket_left(20.f, (GetScreenHeight() / 2.f), racket_width,
                     racket_height, 700.f);

  Racket racket_right(GetScreenWidth() - 20.f, (GetScreenHeight() / 2.f),
                      racket_width, racket_height, 700.f);

  while (!WindowShouldClose()) {

    int screen_width = GetScreenWidth();

    int screen_height = GetScreenHeight();
    ball.x += ball.speedx * GetFrameTime() * getRandomNumber();
    ball.y += ball.speedy * GetFrameTime() * getRandomNumber();

    if (ball.y > screen_height - ball.radius) {
      ball.y = screen_height - ball.radius;
      ball.speedy *= -1;
    }

    if (ball.y < 0 + ball.radius) {
      ball.y = 0 + ball.radius;
      ball.speedy *= -1;
    }

    if (IsKeyDown(KEY_W) && racket_left.y > racket_left.height / 2.0) {
      racket_left.y -= racket_left.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_S) &&
        racket_left.y < screen_height - racket_left.height / 2.0) {
      racket_left.y += racket_left.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP) && racket_right.y > 0 + racket_right.height / 2.0) {
      racket_right.y -= racket_right.speed * GetFrameTime();
    }

    if (IsKeyDown(KEY_DOWN) &&
        racket_right.y < screen_height - racket_right.height / 2.0) {
      racket_right.y += racket_right.speed * GetFrameTime();
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                racket_right.get_rect()) &&
        ball.speedx > 0) {
      ball.speedx *= -1.01f;
      ball.speedy = (ball.y - racket_right.y) / (racket_left.height / 2) * -1 *
                    ball.speedx;
    }
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                racket_left.get_rect()) &&
        ball.speedx < 0) {
      ball.speedx *= -1.01f;
    }

    if (ball.x <= 0) {
      winner_text = "Right Nigga Won!";
    } else if (ball.x >= screen_width) {
      winner_text = "Left Nigga Won!";
    }

    if (winner_text && IsKeyPressed(KEY_SPACE)) {
      ball.x = screen_width / 2;
      ball.y = screen_height / 2;
      ball.speedx = 300;
      ball.speedy = 300;

      winner_text = nullptr;
    }

    BeginDrawing();
    ClearBackground(BLACK);
    ball.Draw();
    racket_left.Draw();
    racket_right.Draw();

    if (winner_text) {
      int text_width = MeasureText(winner_text, 60);
      DrawText(winner_text, (screen_width - text_width) / 2,
               screen_height / 2 - 30, 60, YELLOW);
    }

    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
  std::cout << "End";
  return 0;
}
