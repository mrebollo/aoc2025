/*
    Advent of code - Day 3 (2)
    Find the highest N-digit number in a sequence.
    Greedy version: 
    - select largest digit in [0,end-N] -> i
    - select next largest digit in [i+1,end-(N-1)] -> j
    - repeat until N digits selected
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//#define DEBUG 1
#define DIGITS 12

// Algoritmo greedy: seleccionar los dígitos más grandes disponibles para cada posición
long long find_joltage(const string& line) {    
    long long result = 0;
    int max_idx = 0;
    // Para cada una de las DIGITS posiciones del resultado
    for (int pos = 0; pos < DIGITS; pos++) {
        // Necesitamos reservar espacio para los últimos dígitos 
        int remaining = DIGITS - pos - 1;
        int last = line.size() - remaining;
        // Buscar el dígito más grande en el rango válido
        char max_digit = '0';
        for (int i = max_idx; i < last; i++) {
            if (line[i] > max_digit) {
                max_digit = line[i];
                max_idx = i;
            }
        }
        result = result * 10 + (max_digit - '0');
        max_idx++;
    }
    return result;
}

int main() {
    ifstream input("input.txt");
    string line;
    long long sum = 0;
    while(getline(input, line)){
        long long joltage = find_joltage(line);
#ifdef DEBUG
        cout << "Line: " << line << " -> " << joltage << endl;
#endif
        sum += joltage;
    }
    input.close();
    cout << "Total joltage: " << sum << endl;
    return 0;
}
