#include <vector>

enum CellStates {
    DEAD = 0,
    ALIVE = 1,
    BORDER = 2
};

class Cell;
std::vector<std::vector<Cell>> cells;

class Cell {
public:
    int x, y, state, nextState;

    Cell() : x(0), y(0), state(0), nextState(0) {};

    int getAliveNeighbours() {
        int neighbours = 0;

        if (cells[y-1][x-1].state == CellStates::ALIVE) neighbours++;
        if (cells[y][x-1].state == CellStates::ALIVE) neighbours++;
        if (cells[y-1][x].state == CellStates::ALIVE) neighbours++;
        if (cells[y+1][x+1].state == CellStates::ALIVE) neighbours++;
        if (cells[y][x+1].state == CellStates::ALIVE) neighbours++;
        if (cells[y+1][x].state == CellStates::ALIVE) neighbours++;

        return neighbours;
    }

    void calculateState() {
        if (state == CellStates::BORDER) return;

        int alive = getAliveNeighbours();
        
        if (alive < 2 || alive > 3)
            nextState = CellStates::DEAD;
        else
            nextState = CellStates::ALIVE;
    }
};

void setStates() {
    for (int i = 0; i < cells.size(); i++) 
        for (int j = 0; j < cells[i].size(); j++)
            if (cells[i][j].state != CellStates::BORDER)
                cells[i][j].state = cells[i][j].nextState;
}