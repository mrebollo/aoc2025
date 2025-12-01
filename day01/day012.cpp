/*
    Advent of code 2025. Day 1 (1)
    Count shifts in a circular array stopping in zeros
*/

#include <iostream>
#include <fstream>
#include <vector>

#define SIZE 100

class CircularArray{
private:
    int pos;
    bool zeros;
    void left(int dist){
        zeros = dist > pos && pos != 0;
        pos = (pos - dist + SIZE) % SIZE;
    }
    void right(int dist){
        zeros = (pos + dist) > SIZE;
        pos = (pos + dist) % SIZE;
    }
public:
    CircularArray(): pos(50), zeros(false) {}   
    int move(char dir, int value){
        if(dir == 'R'){
            right(value);
        } else{
            left(value);
        }
        return pos;
    }
    bool crossed() {return zeros;}
};


int vueltas(int* value){
    int vueltas = *value / SIZE;
    *value %= SIZE;
    return vueltas;
}
    
int password(){
    std::ifstream fp("input.txt");
    CircularArray dial;
    char dir;
    int value;
    int num_ceros = 0;
    while(fp >> dir >> value){
        num_ceros += vueltas(&value);
        if (dial.move(dir, value) == 0 || dial.crossed())
            num_ceros++;
    }
    fp.close();
    return num_ceros;
}


int main(){
    std::cout << "The password is: " << password() << std::endl;
    return 0;
}