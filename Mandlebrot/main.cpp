#include <raylib.h>
#include <uchar.h>

#include <cmath>
#include <complex>

template <typename T>
T lerp(const T &a, const T &b, double t)
{
    return (1 - t) * a + t * b;
}

int is_in_set(std::complex<double> c)
{
    std::complex<double> z(0, 0);
    for (int i = 0; i < 500; i++)
    {
        z = std::pow(z, 2) + c;
        if (std::norm(z) > 10.0)
        {
            return i;
        }
    }
    return 0;
}

Color getColor(int iters)
{
    if (iters == 0) return BLACK;  // Set color to specified dark blue for points inside the Mandelbrot set

    float t = static_cast<float>(iters) / 1000.0f;  // Normalize to range [0, 1]

    // Use a darker shade of blue for points outside the Mandelbrot set
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.5f - 0.5f * cos(t * 20.0f + 16 * 2);  // Animate color based on time

    return Color{static_cast<char8_t>(r * 255), static_cast<char8_t>(g * 255), static_cast<char8_t>(b * 255), 255};
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int gridSize = 1000;

    InitWindow(screenWidth, screenHeight, "Mandelbrot Set Animation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);  // Set background color to black
        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                double double_point_x =
                    lerp(static_cast<double>(-2.0), static_cast<double>(2.0), static_cast<double>(x) / gridSize);
                double double_point_y =
                    lerp(static_cast<double>(-2.0), static_cast<double>(2.0), static_cast<double>(y) / gridSize);
                int iters = is_in_set(std::complex<double>(double_point_x, double_point_y));
                Color color = getColor(iters);
                DrawPixel(x * screenWidth / gridSize, y * screenHeight / gridSize, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
