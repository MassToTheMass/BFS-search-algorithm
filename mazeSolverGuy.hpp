#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <vector>
#pragma once


template<size_t n, size_t m>
class MazeSolverGuy {

    private:
        std::queue<std::pair<int, int>> maze_location_queue;
        std::pair<int, int> current_position = {0, 0};
        int (&maze)[n][m];
        std::vector<std::pair<int, int>> visited_locations;
        std::pair<int, int> maze_end_location;

        int (&visual_maze)[n][m];

        void updateVisualMaze() {

            int locations_end = visited_locations.size() - 1;

            visual_maze[current_position.first][current_position.second] = 8;
            visual_maze[visited_locations.at(locations_end).first][visited_locations.at(locations_end).second];

        }

        void checkOrthogonal() {

            std::set<std::pair<int, int>> orthogonal_locations = {
                {current_position.first, current_position.second + 1},
                {current_position.first, current_position.second - 1},
                {current_position.first + 1, current_position.second},
                {current_position.first - 1, current_position.second}
            };

            std::set<std::pair<int, int>>::iterator first = orthogonal_locations.begin();
            std::set<std::pair<int, int>>::iterator last = orthogonal_locations.end();

            std::vector<std::pair<int, int>>::iterator first_visited = visited_locations.begin();
            std::vector<std::pair<int, int>>::iterator last_visited = visited_locations.end();

            while (first != last) {

                while (first_visited != last_visited) {

                    if (*first == *first_visited) {
                        
                        orthogonal_locations.erase(*first);
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
                maze_location_queue.push(*first);

                ++first;
            }
        }

        std::string getMazeString() {

            std::string current_string = "====================================\n";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {

                    current_string += std::to_string(visual_maze[i][j]) + " ";

                }
                current_string += " \n";
            }

            return current_string;
        }

    public:
        MazeSolverGuy(int (&maze)[n][m]) : maze(maze), visual_maze(maze) {
            maze_location_queue.push({0, 0});
            maze_end_location = {n - 1, m - 1};
        }

        void solveMazeBFS() {

            if (maze_location_queue.empty()) {
                std::cout << "Maze could not be solved.\n";
                return;
            }

            current_position = maze_location_queue.front();
            maze_location_queue.pop();

            if (current_position == maze_end_location) {
                std::cout << "Maze Solved!" << std::endl;
                return;
            }

            checkOrthogonal();
            maze_location_queue.pop();
            current_position = maze_location_queue.front();
            visited_locations.push_back(maze_location_queue.front());
            updateVisualMaze();
            std::cout << getMazeString();
            solveMazeBFS();

        }
};