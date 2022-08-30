#include <stdio.h>
#include <random>
#include <chrono>
#include <cstdlib>

#include "cell.hpp"

std::mt19937 mersenne;

int random(int a, int b) {
    std::uniform_int_distribution<> rng{a, b};
    return rng(mersenne);
}

void reset(int length, int lines, int density) {
    cells.clear();

    for (int i = 0; i < lines; i++) 
        cells.emplace_back(std::vector<Cell>(length, Cell()));

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < length; j++) {
            cells[i][j].x = j;
            cells[i][j].y = i;

            if (i == 0 || i == lines-1 || j == 0 || j == length-1) {
                cells[i][j].state = CellStates::BORDER;
                continue;
            }

            if (random(1, 4 * density) == 1)
                cells[i][j].state = CellStates::ALIVE;
        }
    }
}

void print(int generationNumber) {
    printf("Generation %d \n---------------------", generationNumber);
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            if (cells[i][j].state == CellStates::ALIVE) {
                printf("\u001b[32m%d\u001b[0m ", cells[i][j].state);
                continue;
            }

            if (cells[i][j].state == CellStates::DEAD)
                printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int lines, length, density, seed;

    printf("Lines: ");
    scanf("%d", &lines);
    printf("Length: ");
    scanf("%d", &length);
    printf("Density: ");
    scanf("%d", &density);
    printf("Seed (0 - random seed): ");
    scanf("%d", &seed);

    if (seed == 0) {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        mersenne = std::mt19937{static_cast<std::mt19937::result_type>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count())};
    } else {
        mersenne = std::mt19937{static_cast<std::mt19937::result_type>(seed)};
    }

    reset(length, lines, density);

    int generationNumber = 1;

    while (1) {
        #ifdef WINDOWS
            std::system("cls");
        #else
            std::system("clear");
        #endif

        for (int i = 0; i < cells.size(); i++)
            for (int j = 0; j < cells[i].size(); j++)
                cells[i][j].calculateState();

        print(generationNumber);
        
        char get = getchar();
        if ((int)get == 32) {
            generationNumber = 0;
            reset(length, lines, density);
            continue;
        }

        setStates();
        generationNumber++;
    }
}