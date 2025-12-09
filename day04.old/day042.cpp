/*
    Advent of Code 2025 - Day 4 (2)
    Find cells rounded by less that 4 rolls in a grid. 
    Repeat until noe is
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

int remove_rolls(vector<string>& grid) {
    int removed = 0;
    // list of rolls to remove (wait until all grid processed)
    vector<pair<int, int>> to_remove;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == '@' && around(grid, i, j) < 4) 
                    to_remove.push_back({i, j});
        }
    }
    // remove rolls
    for (auto& cell : to_remove) {
        grid[cell.first][cell.second] = '.';
        removed++;
    }
    return removed;
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
    int accesible = 0;
    int removed = 0;
    do{
        removed = remove_rolls(grid);
        accesible += removed;
    } while(removed > 0);

    cout << "Total accesible rolls: " << accesible << endl;
    return 0;
}