#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
class Grid {
  size_t _rows;
  size_t _cols;
  size_t _cell_size;
  std::vector<std::vector<int>> _cells;

  bool in_bounds(int r, int c);

public:
  Grid() = default;
  Grid(size_t rows, size_t cols, size_t cell_size, int x)
      : _rows(rows), _cols(cols), _cell_size(cell_size),
        _cells(rows, std::vector<int>(cols, x)) {
    if (rows % cell_size != 0 || cols % cell_size != 0) {

      throw "ERROR: Rows/Cols not div. by cells_size";
      std::cerr << "ERROR: Rows/Cols not div. by cells_size";
    };
  };

  void Draw();
  void set_value(size_t r, size_t c, size_t val);
  int get_val(int r, int c);
  size_t rows() { return _rows; }
  size_t cols() { return _cols; }
  void fill_random();
};
