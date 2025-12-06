/*
    Advent of code 205 - Day 6 (2)
    Transpose entry and process by rows
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
const string INPUT_FILE = "input.txt";

#define DEBUG 1

int line_length() {
    ifstream input(INPUT_FILE);
    string line;
    getline(input, line);
    input.close();
    return line.length();
}

string extract_values(vector<string>& s) {
    ifstream input(INPUT_FILE);
    string line;
    while (getline(input, line)) {
        if (ispunct(line[0])) break;
        //read each character and push transposed in s
        int i = 0;
        for (char c : line)
            s[i++].push_back(c);
    }
    input.close();
    return line; // returns line with operators
}


long long sum_stack(vector<string>&  s, int &i) {
    long long total = 0;
    while(s[i].find_first_not_of(' ') != std::string::npos)
        total += stoi(s[i++]);  
    i++;
    return total;
}

long long prod_stack(vector<string>&  s, int &i) {
    long long total = 1;
    while(s[i].find_first_not_of(' ') != std::string::npos)
        total *= stoi(s[i++]);
    i++;
    return total;
}

long long process(vector<string>& s, const string& ops) {
    long long total = 0;
    stringstream ss(ops);
    char op;
    int i = 0;
    while(ss >> op){
        long long total_stack = (op == '+' ) ? sum_stack(s,i) : prod_stack(s,i);
#ifdef DEBUG
        cout << i << "(" << op << "): " << total_stack << endl;
#endif
        total += total_stack;
    }
    return total;
}

int main() {
    vector<string> sheet(line_length());
    string ops = extract_values(sheet);
#ifdef DEBUG
    for (string num: sheet)
        cout << num << endl;
#endif
    long long result = 0;
    result = process(sheet, ops);
    cout << "Final result: " << result << endl;
    return 0;
}