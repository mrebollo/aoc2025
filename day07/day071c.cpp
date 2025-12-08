/*
    Advent of Code 2025 - Day 7 (1) - DP version
    Calcula cuántos caminos llegan al final usando programación dinámica ascendente
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ifstream input("input.txt");
    string line;
    vector<string> grid;
    int start_col = -1;
    // Leer la posición de S
    getline(input, line);
    start_col = line.find('S');
    // Leer el resto del grid
    while (getline(input, line)) {
        if (!line.empty()) grid.push_back(line);
    }
    input.close();
    int rows = grid.size();
    int cols = grid[0].size();
    // DP: dp[fila][columna] = caminos que llegan a esa celda
    vector<vector<long long>> dp(rows+1, vector<long long>(cols, 0));
    dp[0][start_col] = 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (dp[i][j] == 0) continue;
            if (grid[i][j] == '^') {
                if (j-1 >= 0) dp[i+1][j-1] += dp[i][j];
                if (j+1 < cols) dp[i+1][j+1] += dp[i][j];
            } else {
                dp[i+1][j] += dp[i][j];
            }
        }
    }
    // Sumar caminos que llegan a la última fila
    long long total = 0;
    for (int j = 0; j < cols; ++j) total += dp[rows][j];
    cout << "Caminos que llegan al final: " << total << endl;
    return 0;
}
