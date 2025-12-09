/*
    Advent of Code 2025 - Day 4 (1)
    Find cells rounded by less that 4 rolls in a grid
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define DEBUG

int around(const vector<string>& grid, int i, int j) {
    int count = 0;
    int directions[8][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}}; // up, down, left, right, and diagonals
    for (auto& dir : directions) {
        int row = i + dir[0];
        int col = j + dir[1];
        if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size()) {
            if (grid[row][col] == '@') 
                count++;
        }
    }
    return count;
}

int main() {
    ifstream input("input.txt");
    // load grid from file
    string line;
    vector<string> grid;
    while(getline(input, line))
        grid.push_back(line);
    input.close();
    // count accesible rolls
    int acesible = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@' && around(grid, i, j) < 4) {
                    acesible++;
#ifdef DEBUG
                    cout << 'x';
#endif
            } 
#ifdef DEBUG
            else {
                cout << grid[i][j];
            }
#endif
        }
#ifdef DEBUG
        cout << endl;
#endif 
    }   
    cout << "Total accesible rolls: " << acesible << endl;
    return 0;
}