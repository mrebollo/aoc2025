/*
    Advent of Code 2025 - Day 10 (1)
    Shortets combination of button press to set light pattern
    Bitwise + bfs
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

#define DEBUG 1

class Machine{
private:
    int num_buttons;
    int light_panel;
    vector<int> button_masks; // bitmask for each button

    void insertButton(int mask) {
        button_masks.push_back(mask);
        num_buttons++;
    }

    void pushButton(int button_index) {
        light_panel ^= button_masks[button_index];
    }
    
    bool operator ==(int pattern) const {
        return (this->light_panel == pattern);
    }
    
    void addButton(string token);
    void setLightPattern(string token);
public:
    Machine(): num_buttons(0), light_panel(0) {}
    int set(string machine);
    int findPattern(int pattern) {return 0;}
};

string print(int mask) {
    string result;
    for(int i = 9; i >= 0; i--) {
        if( mask & (1 << i) )
            result += '#';
        else
            result += '.';
    }
    return result;
}

void Machine::setLightPattern(string token) {
    int last = token.size()-1;
    for(int i = 1; i < last; i++) {
        if( token[i] == '#' )
            light_panel |= (1 << (i-1));
    }
#ifdef DEBUG
    cout << "Pannel " << token <<  " " << light_panel << endl;
#endif
}

void Machine::addButton(string token){
    int mask = 0;
#ifdef DEBUG
    cout << "Adding " << token;
#endif
    //remove parenthhesis
    token.pop_back();
    token.erase(token.begin());
    stringstream ss(token);
    int bit;
    char comma;
    while(ss >> bit) {
        mask |= (1 << bit);
        ss >> comma;
    }   
#ifdef DEBUG
    cout << " " << print(mask) << endl;
#endif
    insertButton(mask);
}

int Machine::set(string line) {
    stringstream ss(line);
    light_panel = 0;
    button_masks.clear();
    num_buttons = 0;
    string token;
    // skip the lights
    getline(ss, token, ' '); // skip "LIGHTS"
    setLightPattern(token);
    // read buttons
    while(getline(ss, token, ' ')) {
        // end when joltage pattern starts
        if (token[0] == '{') break;
        addButton(token);
    }
    return light_panel;
}

int main(){
    ifstream input("test.txt");
    string line;
    int total_presses = 0;
    while(getline(input, line)) {
        Machine m = Machine();
        int pattern = m.set(line);
        int presses = m.findPattern(pattern);
#ifdef DEBUG
        cout << "Pattern " << pattern << " found in " << presses << " presses." << endl;
#endif
        total_presses += presses;
    }
    input.close();
    cout << "Total presses: " << total_presses << endl;
}