#include "mazeSolverGuy.hpp"

int main() {

    int maze1[5][5] = {
        {0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0}
    }; 

    MazeSolverGuy<5, 5> maze1_solver(maze1);

    maze1_solver.solveMazeBFS();

    return 0;
}