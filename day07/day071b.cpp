/*
    Advent of Code 2025 - Day 7 (1)
    Use the matiz to trace the beam propagation (cost m*n) 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

//#define DEBUG 1

int load(vector<string>& grid) {
    ifstream input("input.txt");
    string line;
    getline(input, line);
    int spos = line.find('S');
    while (getline(input, line)) {
        if (!line.empty()) grid.push_back(line);
    }
    input.close();
    grid[0][spos] = '|';
    return spos;
}

void save(const vector<string>& grid) {
    ofstream output("output.txt");  
    for (const auto& row : grid) 
        output << row << endl;
    output << endl;
    output.close();
}


int propagate(vector<string>& grid, int row) {
    int splits = 0;
    int ncol = grid[0].size();
    // crece desde el centro a los laterales -> optimizar recorido por columnas
    int first = ncol / 2 ;
    int last = ncol / 2;
    while (row < (int)grid.size()-2) {
        for(int col = first; col <= last; col++) {
            if (grid[row][col] == '|'){
                if(grid[row+1][col] == '^') {
                    // split in next row from splitter 
                    grid[row+2][col-1] = '|';
                    grid[row+2][col+1] = '|';
                    splits++;
#ifdef DEBUG
                    grid[row+1][col-1] = '|';
                    grid[row+1][col+1] = '|';
                    grid[row+1][col] = '#'; // mark activated splitter 
                    cout << "(" << row+1 << ", " << col << ") activated" << endl; 
#endif
                } else  {
                    // continue downwards
#ifdef DEBUG
                    grid[row+1][col] = '|';
#endif
                    grid[row+2][col] = '|';
                }
            }
        }
         row += 2;
         first--;
         last++;
    }
    return splits;
}

int main() {
    vector<string> grid;
    load(grid);
    int splits = propagate(grid, 0);
#ifdef DEBUG
    save(grid);
#endif
    cout << "Activated splitters: " << splits << endl;
    return 0;
}
