/*
    Advent of Code 2025 - Day 7 (1)
    Count how many paths reach the end: 
    Each splitter sums +1 to left and to right
    Bruteforce
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

//#define DEBUG 1
#define SPLITTER -1

long long load(vector<vector<long long>>& grid) {
    ifstream input("input.txt");
    string line;
    getline(input, line);
    int spos = line.find('S');
    do{
        vector<long long> row;
        for(char c : line) 
            row.push_back( c == '.' ? 0 : SPLITTER );
        grid.push_back(row);
    } while (getline(input, line));
    grid[0][spos] = 1; // start position
    grid[1][spos] = 1; // start position
    input.close();
    return spos;
}

void save(const vector<vector<long long>>& grid) {
    ofstream output("output.txt");  
    for (const auto& row : grid) {
        for (const auto& val : row) {
            if (val == -1)
                output << '^ ';
            else
                output << val << ' ';
        }
        output << endl;
    }
    output << endl;    
    output.close();
}

void print (const vector<vector<long long>>& grid) {
    for (const auto& row : grid) {
        for (const auto& val : row) {
            if (val == -1)
                cout << '^';
            else
                cout << val;
        }
        cout << endl;
    }
    cout << endl;
}


long long propagate(vector<vector<long long>>& grid, int row) {
    int ncol = grid[0].size();
    while (row < (int)grid.size()-2) {
        for(int col = 0; col < ncol; col++) {
            if (grid[row][col] > 0){
                if(grid[row+1][col] == SPLITTER) {
                    // split in next row from splitter 
                    grid[row+1][col-1] += grid[row][col];
                    grid[row+1][col+1] += grid[row][col];
                    grid[row+2][col-1] = grid[row+1][col-1];
                    grid[row+2][col+1] = grid[row+1][col+1];
                } else  {   
                    // continue downwards
                    grid[row+1][col] += grid[row][col];
                    grid[row+2][col] = grid[row+1][col];
                }
            }
        }
         row+=2;
    }
    long long paths = 0;
    for(int col = 0; col < ncol; col++)
        paths += grid[grid.size()-1][col];
    return paths;
}

int main() {
    vector<vector<long long>> grid;
    load(grid);
    long long paths = propagate(grid, 1);
#ifdef DEBUG
    print(grid);
#endif
    save(grid);
    cout << "Total paths: " << paths << endl;
    return 0;
}
