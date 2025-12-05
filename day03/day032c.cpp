/*
    Advent of code - Day 3 (2)
    Dynamic Programming approach 
    memo[i][k] = best number with k digits that can be formed 
                 from position i to the end
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

//#define DEBUG 1
#define NUM_DIGITS 12


long long find_joltage(int pos, int digits, const string& line, vector<vector<long long>>& memo) {
    int n = line.size();
    // Si ya calculamos este estado lo devolvemos
    if (memo[pos][digits] != -1) return memo[pos][digits];
    // Caso base 1: no quedan dígitos por formar (ha creado el número completo)
    if (digits == 0) return 0;
    // Caso base 2: ya no hay suficientes caracteres (no se puede formar el número)
    if (pos >= n || n - pos < digits) return -1;
    
    long long best = -1;
    // Opción 1: No usar el dígito en 'pos', buscar desde pos+1
    best = max(best, find_joltage(pos + 1, digits, line, memo));
    // Opción 2: Usar el dígito en 'pos'. Buscar la mejor secuencia con uno menos
    long long rest = find_joltage(pos + 1, digits - 1, line, memo);
    if (rest != -1) {
        long long combined = (line[pos] - '0') * pow(10, digits - 1) + rest;
        best = max(best, combined);
    }
    memo[pos][digits] = best;
    return best;
}


int main() {
    ifstream input("input.txt");
    string line;
    long long sum = 0;
    
    // Inicializar la tabla de memoización (memo)
    const int MAX_LINE_LENGTH = 200; // Ajustar según sea necesario    
    while(getline(input, line)){
        vector<vector<long long>> memo(MAX_LINE_LENGTH + 1, vector<long long>(NUM_DIGITS + 1, -1));
        long long result = find_joltage(0, NUM_DIGITS, line, memo);
    #ifdef DEBUG
        cout << "Line: " << line << " -> " << result << endl;
    #endif
        sum += result;
    }
    input.close();
    cout << "Total joltage: " << sum << endl;
    return 0;
}
