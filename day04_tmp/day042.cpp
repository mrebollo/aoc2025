/*
    Advent of Code 2025 - Day 4 (2)
    Count rolls of paper roeunded by less of 4 rolls
    Re`peat until no more rolls can be removed

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define DEBUG 0

// Directions for 8 adjacent positions (including diagonals)
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};


void load(vector<string>& grid) {
    ifstream input("input.txt");
    string line;
    while (getline(input, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    input.close();
}


inline int inside(int i, int j, int rows, int cols) {
    return (i >=0 && i < rows && j >=0 && j < cols);
}   


int count_around(const vector<string>& grid, int x, int y) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        // Check bounds and if there's a roll
        if (inside(nx, ny, grid.size(), grid[0].size()) && grid[nx][ny] == '@')
            count++;
    }
    return count;
}


// Count adjacent rolls (@) around position (x, y)
int accesible( vector<string>& grid) {
    int total = 0;
    for(int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[0].size(); j++) {
            if (grid[i][j] == '@' && count_around(grid, i, j) < 4){
                total++;
            }
        }
    }
    return total;
}


void print( const vector<string>& grid) {
    for (const auto& row : grid) {
        cout << row << endl;
    }
    cout << endl;
}


int main() {
    
    vector<string> grid;
    load(grid);
    int total = accesible(grid);
    print(grid);
    cout << "Accessible rolls: " << total << endl;
    return 0;
}
