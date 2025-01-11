#include <queue>
#include <set>
#include <iostream>
#include <string>
#pragma once


template<size_t n, size_t m>
class MazeSolverGuy {

    private:
        std::queue<std::pair<int, int>> maze_location_queue;
        std::pair<int, int> current_position = {0, 0};
        int (&maze)[n][m];
        std::set<std::pair<int, int>> visited_locations;
        std::pair<int, int> maze_end_location;

        int (&visual_maze)[n][m];

        void debugMessage() {
            
            std::cout << "Top of Queue:" << maze_location_queue.front().first << " : " << maze_location_queue.front().second << std::endl;
            std::cout << "Current Location:" << current_position.first << " : " << current_position.second << std::endl;
            std::cout << "End Location:" << maze_end_location.first << " : " << maze_end_location.second << std::endl;
        }

        void updateVisualMaze() {

            for (const auto& pair : visited_locations) {
                visual_maze[pair.first][pair.second] = 7;
            }
            visual_maze[current_position.first][current_position.second] = 8;

        }

        void checkOrthogonal() {

            std::set<std::pair<int, int>> orthogonal_locations = {
                {current_position.first, current_position.second + 1},
                {current_position.first, current_position.second - 1},
                {current_position.first + 1, current_position.second},
                {current_position.first - 1, current_position.second}
            };

            std::set<std::pair<int, int>> locations_to_remove;

            for (const auto& pair : orthogonal_locations) {

                std::cout << "pair in question:: " << pair.first << ":" << pair.second << std::endl;
                std::cout << "pair.first < 0:      " << (pair.first < 0) << std::endl;
                std::cout << "pair.second < 0:      " << (pair.second < 0) << std::endl;
                std::cout << "pair.first > n:      " << (pair.first > n) << std::endl;
                std::cout << "pair.second > m:      " << (pair.first > n) << std::endl;
                std::cout << "!maze[pair.first][pair.second]:      " << (!maze[pair.first][pair.second]) << std::endl;

                

                if ((pair.first < 0 || pair.second < 0 || pair.first > n || pair.second > m) || maze[pair.first][pair.second]) {

                    locations_to_remove.insert(pair);
                }

                for (const auto& visited_pair : visited_locations) {

                    if (pair == visited_pair) {

                        locations_to_remove.insert(pair);
                        break;
                    }
                }
            }

            for (const auto& pair : locations_to_remove) {
                orthogonal_locations.erase(pair);
            }

            for (const auto& pair : orthogonal_locations) {

                std::cout << "Added Pair: " << pair.first << ":" << pair.second << std::endl;

                maze_location_queue.push(pair);
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

                debugMessage();
                
                current_position = maze_location_queue.front();
                maze_location_queue.pop();

                checkOrthogonal();
                visited_locations.insert(current_position);

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