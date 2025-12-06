/*
    Advent of code 205 - Day 6 (1)
    Suma de operaciones por columnas
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
const string INPUT_FILE = "input.txt";

#define DEBUG 1

int num_operations() {
    ifstream input(INPUT_FILE);
    string line;
    getline(input, line);
    input.close();

    int op, count = 0;
    stringstream ss(line);
    while (ss >> op) 
        count++;
    return count;
}

string extract_values(vector<stack<int>>& s, ifstream& input, int operations) {
    string line;
    int value;
    while (getline(input, line)) {
        // detect first line with operators -> ends
        if (ispunct(line[0])) return line;
        stringstream ss(line);
        for (int i = 0; i < operations; i++){
            ss >> value;
            s[i].push(value);
        }
    }
}

long long sum_stack(stack<int>& s) {
    long long total = 0;
    while (!s.empty()) {
        total += s.top();
        s.pop();
    }
    return total;
}

long long prod_stack(stack<int>& s) {
    long long total = 1;
    while (!s.empty()) {
        total *= s.top();
        s.pop();
    }
    return total;
}

long long process(vector<stack<int>>& columns, const string& ops, int operations) {
    long long total = 0;
    stringstream ss(ops);
    char op;
    int i = 0;
    while(ss >> op){
        long long total_stack = (op == '+' ) ? sum_stack(columns[i]) : prod_stack(columns[i]);
#ifdef DEBUG
        cout << i << "(" << op << "): " << total_stack << endl;
#endif
        total += total_stack;
        i++;
    }
    return total;
}


int main() {
    int operations = num_operations();
    // create a stack for each column
    vector<stack<int>> columns(operations);
    // read input file again to fill the stacks
    ifstream input(INPUT_FILE);
    string ops = extract_values(columns, input, operations);
    cout << "Number of operations: " << operations << endl;   
    input.close();
    long long result = 0;
    result = process(columns, ops, operations);
    cout << "Final result: " << result << endl;
    return 0;
}