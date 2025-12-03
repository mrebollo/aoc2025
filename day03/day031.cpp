/*
    Day 3 (1)
    Find the highest two-digit number in a secuence.
    Brute force approach.
*/

#include <iostream>
#include <fstream>
#include <string>   
using namespace std;

//#define DEBUG

int find_joltage(const string& line) {
    int max_joltage = 0;
    for (size_t i = 0; i < line.size() - 1; i++) {
        for(size_t j = i + 1; j < line.size(); j++){
            int jolts = (line[i] - '0') * 10 + (line[j] - '0');
            if (jolts > max_joltage) 
                max_joltage = jolts;
        }
    }
    return max_joltage;
}


int main() {
    ifstream input("input.txt");
    string line;
    int sum = 0;
    while(getline(input, line)){  
        int joltage = find_joltage(line);
#ifdef DEBUG
        cout << "Line: " << line << " -> " << joltage << endl;
#endif
        sum += joltage;
    }
    input.close();
    cout << "Total joltage: " << sum << endl;
    return 0;
}