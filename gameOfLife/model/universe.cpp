#include "Universe.h"
#include <fstream>

Universe::Universe(int rows, int cols)
    : rows(rows), cols(cols),
      grid(rows, std::vector<bool>(cols, false)),
      nextGrid(rows, std::vector<bool>(cols, false)) {}

int Universe::countNeighbors(int x, int y) const {
    static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int count = 0;
    for (int i = 0; i < 8; ++i) {
        int nx = (x + dx[i] + rows) % rows;
        int ny = (y + dy[i] + cols) % cols;
        if (grid[nx][ny]) ++count;
    }
    return count;
}

void Universe::tick() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            int neighbors = countNeighbors(i, j);
            nextGrid[i][j] = grid[i][j] ? (neighbors == 2 || neighbors == 3) : (neighbors == 3);
        }
    grid.swap(nextGrid);
}

void Universe::setCell(int x, int y, bool alive) {
    if (x >= 0 && x < rows && y >= 0 && y < cols)
        grid[x][y] = alive;
}


const std::vector<std::vector<bool>>& Universe::getGrid() const {
    return grid;
}
