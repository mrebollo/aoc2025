/*
    Advent of code - Day 3 (2)
    Greedy Recursive
    Implementación recursiva del algoritmo greedy (no gana nada en eficiencia)
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

//#define DEBUG 1
#define DIGITS 12


// Versión recursiva del greedy: construye el número directamente
// En cada llamada recursiva, encontramos el dígito más grande válido
// y continuamos desde la siguiente posición
long long greedy_recursive(const string& line, int start, int remaining) {
    // Caso base: no quedan más dígitos por seleccionar
    if (remaining == 0)
        return 0;
    // Buscar el dígito más grande en el rango válido
    remaining--;
    int last = line.size() - remaining;
    char max_digit = '0';
    int max_idx = start;
    for (int i = start; i < last; i++) {
        if (line[i] > max_digit) {
            max_digit = line[i];
            max_idx = i;
        }
    }
    // Construir el resultado: este dígito * 10^(remaining) + resultado recursivo
    return (max_digit - '0') * pow(10, remaining) + greedy_recursive(line, max_idx + 1, remaining);
}

int main() {
    ifstream input("input.txt");
    string line;
    long long sum = 0;
    
    while(getline(input, line)){
        long long joltage = greedy_recursive(line, 0, DIGITS);
#ifdef DEBUG
        cout << "Line: " << line << " -> " << joltage << endl;
#endif
        sum += joltage;
    }
    input.close();
    
    cout << "Total joltage: " << sum << endl;
    return 0;
}
