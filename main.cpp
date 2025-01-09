#include "mazeSolverGuy.hpp"

void solveMazeBFS(int (&arr)[n][m]);

int main() {

    int maze1[5][5] = {
        {0, 1, 1, 1, 1},
        {0, 0, 0, 1, 0},
        {1, 1, 0, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 0}
    }; 

    MazeSolverGuy maze1_solver(maze1);

    maze1_solver.solveMazeBFS();


    return 0;
}



void solveMazeBFS(int (&arr)[n][m]) {

    current_maze_end = arr[sizeof(arr) - 1][sizeof(arr[0]) - 1];

    if (current_position != current_maze_end) {}

    maze_location_queue.push(current_position);

}