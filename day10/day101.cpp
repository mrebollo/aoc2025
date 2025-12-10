/*
    Advent of Code 2025 - Day 10 (1)
    Shortets combination of button press to set light pattern
    Bitwise + bfs
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using namespace std;

#define DEBUG 1

class Machine{
private:
    int num_buttons;
    uint16_t light_panel;
    vector<uint16_t> button_masks; // bitmask for each button

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
    uint16_t set(string machine);
    int findPattern(int pattern) {return 0;}
};

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
    stringstream ss(token);
    uint16_t mask = 0;
#ifdef DEBUG
    cout << "Adding " << token;;
#endif
    while(getline(ss, token, ',')) {
        int bit = stoi(token);
        mask |= (1 << bit);
#ifdef DEBUG
    cout << ' ' << mask;
#endif
    }   
#ifdef DEBUG
    cout << " -> " << mask << endl;
#endif
    insertButton(mask);
}

uint16_t Machine::set(string line) {
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