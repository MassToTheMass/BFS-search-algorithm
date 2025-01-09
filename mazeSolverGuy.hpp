#include <queue>
#pragma once
#include <iostream>

template<size_t n, size_t m>
class MazeSolverGuy {

    private:
        std::queue<std::pair<int, int>> maze_location_queue;
        std::pair<int, int> current_position = {0, 0};
        int (&maze)[n][m];
        std::set<std::pair<int, int>> visited_locations;

        void checkOrthogonal() {
            if (!maze[current_location.first][current_location.second + 1]) {
                maze_location_queue.push({current_location.first, current_location.second + 1});
            }
            if (!maze[current_location.first][current_location.second - 1]) {
                maze_location_queue.push({current_location.first, current_location.second - 1});
            }
            if (!maze[current_location.first + 1][current_location.second]) {
                maze_location_queue.push({current_location.first + 1, current_location.second});
            }
            if (!maze[current_location.first - 1][current_location.second]) {
                maze_location_queue.push({current_location.first - 1, current_location.second});
            }
            std::cout << maze_location_queue.front().first << " " << maze_location_queue.front().second << std::endl;
        }
        

    public:
        MazeSolverGuy(int (&maze)[n][m]) : maze(maze) {
            maze_location_queue.push({0, 0});
            maze_end_location = {n - 1, m - 1};
        }

        void solveMazeBFS() {

            if (maze_location_queue.front() == maze_location_queue.back()) {
                if (current_location != maze_end_location) {
                    checkOrthogonal();
                    maze_location_queue.pop();
                    current_location = maze_location_queue.front();
                } else {
                    std::cout << "Maze Solved!" << std::endl;
                }
            }
        }

};