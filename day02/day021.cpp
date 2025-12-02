/*
    Advent of Code 2025 - Day 2 (1)
    Find numbers in ranges defined by two identical pairs
*/

#include <iostream>
#include <fstream>
#include <string>

//#define DEBUG 1

bool is_invalid(long long id){
    std::string id_str = std::to_string(id);
    int len = id_str.length();
    if(len % 2 != 0)
        return false;
    int half = len / 2;
    return id_str.substr(0, half).compare(id_str.substr(half, half)) == 0;
}


long long process_range(long long inf, long long sup){
    long long sum = 0;
    for(long long id = inf; id <= sup; id++){
        if(is_invalid(id)){
#ifdef DEBUG
            std::cout << id << std::endl;
#endif
            sum += id;
        }
    }
    return sum;
}


long long analyze_ids(){
    std::ifstream fp("input.txt");
    long long sum_invalid = 0;
    long long  id, inf, sup;
    char slash, comma;
    while(fp >> inf >> slash >> sup){
#ifdef DEBUG
        std::cout << "Processing ID " << id << " in range [" << inf << ", " << sup << "]\n";
#endif
        sum_invalid += process_range(inf, sup);
        fp >> comma;
    }
    fp.close();
    return sum_invalid;
}


int main(){
    long long sum = analyze_ids();
    std::cout << "Sum of invalid ids: " << sum << std::endl;
    return 0;
}