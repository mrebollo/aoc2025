/*
    Advent of code 2025 - Day 7 (1)
    Calculate how many splitters are activated by a beam
    Brute force with recursion (not for input)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#define DEBUG 1

int load(vector<string>& grid) {
    ifstream input("test.txt");
    string line;
    // get the S position
    getline(input, line);
    int spos = line.find('S');

    // Read the rest of the grid
    while (getline(input, line)) {
        if (!line.empty()) {
            grid.push_back(line);
        }
    }
    input.close();
    return spos;
}

void print(const vector<string>& grid) {
    for (const auto& row : grid) {
        cout << row << endl;
    }
    cout << endl;
}

// final recursion function to propagate tachyons
void propagate(vector<string>& grid, queue<pair<int, int>>& tachyons, int &splits) {
    // CB empty queue
    if (tachyons.empty()) return;
    // extract a tachyon
    pair<int, int> p = tachyons.front();
    tachyons.pop();
#ifdef DEBUG
        grid[p.first][p.second] = '|';
        //print(grid);
#endif
    if(p.first+1 >= (int)grid.size()-1) return; // avoid last row
    // if splitter activated, count it
    if (grid[p.first+1][p.second] == '^') {
        tachyons.push({p.first+1, p.second-1});
        tachyons.push({p.first+1, p.second+1});
#ifdef DEBUG
        grid[p.first+1][p.second] = '#';
        cout << "(" << p.first+1 << ", " << p.second << ") activated" << endl;
#endif
        splits++;
        return propagate(grid, tachyons, splits);
    }
    else{
        tachyons.push({p.first+1, p.second});
        return propagate(grid, tachyons, splits);
    }
}


int main() {
    vector<string> grid;
    int start = load(grid);
    queue<pair<int, int>> tachyons;
    tachyons.push({0, start}); // grid doesn't contain S row
    int splits = 0;
    propagate(grid, tachyons, splits);
    cout << "Activated splitters: " << splits << endl;
    return 0;
}
