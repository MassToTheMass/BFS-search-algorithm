#include <queue>
#include <set>
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

            std::set<std::pair<int, int>> orthogonal_locations = {
                {current_position.first, current_position.second + 1},
                {current_position.first, current_position.second - 1},
                {current_position.first + 1, current_position.second},
                {current_position.first - 1, current_position.second}
            };

            std::set<std::pair<int, int>>::iterator first = orthogonal_locations.begin();
            std::set<std::pair<int, int>>::iterator last = orthogonal_locations.end();

            std::set<std::pair<int, int>>::iterator first_visited = visited_locations.begin();
            std::set<std::pair<int, int>>::iterator last_visited = visited_locations.end();

            while (first != last) {

                while (first_visited != last_visited) {

                    if ({first.first, first.second} == {first_visited.first, first_visited.second}) {
                        
                        visited_locations.erase({first_visited.first, first_visited.second});
                        break;
                    }


                    ++first_visited;
                }

                first_visited = visited_locations.begin();
                ++first;
            }

            first = orthogonal_locations.begin();
            last = orthogonal_locations.end();

            while (first != last) {
                maze_location_queue.push({first.first, first.second});
            }
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
                    solveMazeBFS();
                } else {
                    std::cout << "Maze Solved!" << std::endl;
                }
            }
        }

};