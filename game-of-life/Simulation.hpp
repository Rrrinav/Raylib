#pragma once
#include "grid.hpp"

class gol {

public:
  Grid grid;
  Grid tempGrid;
  gol(size_t rows, size_t cols, size_t cell_size)
      : grid(rows, cols, cell_size, 0), tempGrid(rows, cols, cell_size, 0) {
    grid.fill_random();
  };

  void Draw();
  void set_cell_value(int row, int col, int val);
  int count_live_neighbours(int r, int col);
  void update();
};
