#include "grid.hpp"

#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <random>

#include "raylib.h"

int getRandom(int min, int max)
{
  // Seed the random number generator with the current time
  srand(100);

  // Generate a random value in the range [min, max]
  return static_cast<float>(rand()) / RAND_MAX;
}
void Grid::Draw()
{
  for (size_t row = 0; row < _rows; ++row)
  {
    for (size_t col = 0; col < _cols; ++col)
    {
      Color color = _cells[row][col] == 1 ? Color{4, 102, 200, 225} : Color{51, 65, 92, 255};
      DrawRectangle(col * _cell_size, row * _cell_size, _cell_size - 1, _cell_size - 1, color);
    }
  }
}
bool Grid::in_bounds(int r, int c)
{
  if (r >= 0 && r < _rows && c >= 0 && c < _cols)
    return true;
  else
    return false;
}

void Grid::set_value(size_t r, size_t c, size_t val)
{
  if (in_bounds(r, c))
    _cells[r][c] = val;
}

int Grid::get_val(int r, int c)
{
  if (in_bounds(r, c))
    return _cells[r][c];
  else
    return 0;
}
float RandomValue(float min, float max)
{
  std::random_device rd;
  // Use a random engine and seed it with the random device
  std::mt19937 gen(rd());
  // Use a uniform distribution to generate random numbers in the specified
  // range
  std::uniform_real_distribution<float> dis(min, std::nextafter(max, std::numeric_limits<float>::max()));

  // Generate and return a random number
  return dis(gen);
}

void Grid::fill_random()
{
  for (int row = 0; row < _rows; row++)
  {
    for (int column = 0; column < _cols; column++)
    {
      int randomValue = RandomValue(0, 4);
      _cells[row][column] = (randomValue % 4 == 0) ? 1 : 0;
    }
  }
}
