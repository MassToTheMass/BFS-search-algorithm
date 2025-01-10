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

                std::pair<int, int> pair = *first;

                std::cout << "pair in question: " << pair.first << " : " << pair.second << std::endl;
                std::cout << "indexing what?" << maze[pair.first][pair.second] << std::endl;
                std::cout << "maze[pair.first][pair.second] <= -1: " << (maze[pair.first][pair.second] <= -1) << std::endl;
                std::cout << "maze[pair.first][pair.second] >= 1: " << (maze[pair.first][pair.second] >= 1) << std::endl;


                if ((maze[pair.first][pair.second] <= -1 || maze[pair.first][pair.second] >= 1)) {

                    std::cout << "Pair not allowed" << std::endl;
                    orthogonal_locations.erase(*first);

                }

                while (first_visited != last_visited) {

                    if (pair == *first_visited) {

                        std::cout << "Pair already visited" << std::endl;
                        orthogonal_locations.erase(*first);
                        break;
                    }


                    ++first_visited;
                }


                first_visited = visited_locations.begin();




                









                // These lines might need to be moved ie. when we rtemove something we also are iterating so it can be tricky.
                last = orthogonal_locations.end();
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

            while (!maze_location_queue.empty() && current_position != maze_end_location) {

                std::cout << "Top of Queue:" << maze_location_queue.front().first << " : " << maze_location_queue.front().second << std::endl;
                std::cout << "Current Location:" << current_position.first << " : " << current_position.second << std::endl;
                std::cout << "End Location:" << maze_end_location.first << " : " << maze_end_location.second << std::endl;
                
                current_position = maze_location_queue.front();
                maze_location_queue.pop();

                checkOrthogonal();
                visited_locations.push_back(current_position);

                updateVisualMaze();
                std::cout << getMazeString();

            }

            if (maze_location_queue.empty()) {
                std::cout << "Maze could not be solved.\n";
                return;
            }

            if (current_position == maze_end_location) {
                std::cout << "Maze Solved!" << std::endl;
                return;
            }
        }
};