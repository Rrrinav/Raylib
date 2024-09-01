#include "Simulation.hpp"
#include <raylib.h>
#include <utility>
#include <vector>

void gol::Draw() { grid.Draw(); }

void gol::set_cell_value(int row, int col, int val) {
  grid.set_value(row, col, val);
};

int gol::count_live_neighbours(int row, int col) {
  std::vector<std::pair<int, int>> neighbour_offset = {
      {-1, 0}, {-1, 1}, {1, 0}, {1, 1}, {0, 1}, {0, -1}, {-1, -1}, {1, -1},
  };

  int live_neighbours = 0;
  for (const auto &offset : neighbour_offset) {
    int neighbour_row = (row + offset.first + grid.rows()) % grid.rows();
    int neighbour_col = (col + offset.second + grid.cols()) % grid.cols();
    live_neighbours += grid.get_val(neighbour_row, neighbour_col);
  }
  return live_neighbours;
}

void gol::update() {
  for (int row = 0; row < grid.rows(); row++) {
    for (int column = 0; column < grid.cols(); column++) {
      int liveNeighbors = count_live_neighbours(row, column);
      int cellValue = grid.get_val(row, column);

      if (cellValue == 1) {
        if (liveNeighbors > 3 || liveNeighbors < 2) {
          tempGrid.set_value(row, column, 0);
        } else {
          tempGrid.set_value(row, column, 1);
        }
      } else {
        if (liveNeighbors == 3) {
          tempGrid.set_value(row, column, 1);
        } else {
          tempGrid.set_value(row, column, 0);
        }
      }
    }
  }
  grid = tempGrid;
}
