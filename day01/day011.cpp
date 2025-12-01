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
    void left(int dist){pos = (pos - dist + SIZE) % SIZE;}
    void right(int dist){pos = (pos + dist) % SIZE;}
public:
    CircularArray(): pos(50) {}   
    int move(char dir, int value){
        if(dir == 'R'){
            right(value);
        } else{
            left(value);
        }
        return pos;
    }
};


int password(){
    std::ifstream fp("input.txt");
    CircularArray dial;
    char dir;
    int value;
    int num_ceros = 0;
    while(fp >> dir >> value){
        if (dial.move(dir, value) == 0){
            num_ceros++;
        }
    }
    fp.close();
    return num_ceros;
}


int main(){
    std::cout << "The password is: " << password() << std::endl;
    return 0;
}