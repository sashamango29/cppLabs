#pragma once
#include <vector>

class Universe {
public:
    Universe(int rows, int cols);
    void tick();
    void setCell(int x, int y, bool alive);

    [[nodiscard]] const std::vector<std::vector<bool>>& getGrid() const;

private:
    int rows, cols;
    std::vector<std::vector<bool>> grid, nextGrid;
    [[nodiscard]] int countNeighbors(int x, int y) const;
};
