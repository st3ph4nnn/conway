# conway

Simple recreation of conway the game of life in the terminal using object oriented programming and c++ standard 17.  
Reference: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

# Quick start

Clone the github project.  
And to build, run this command: **g++ main.cpp -o game -std=c++17**. Then open it using ./game

# Features

The alive cells are marked with a green 'O'.  
The dead cells are replaced with whitespace ' '.
Borders exist in the game, because a cell in the right-most up corner would check 5 positions that do not exist in the cell arena (null elements in the matrix). Also they are not marked because i couldn't find a good cross-platform way of SetCursorPos.

Some (cool) features:  
- Custom width and height of the cells canvas
- Random (mersenne twister) cell creation using density (custom seeding available)
- Some ascii coloring
