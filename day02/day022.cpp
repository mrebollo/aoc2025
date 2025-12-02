/*
    Advent of Code 2025 - Day 2 (2)
    Find numbers in ranges defined with repited sequences. Brute force
*/

#include <iostream>
#include <fstream>
#include <string>

//#define DEBUG 1

std::string concat(const std::string &s, int times){
    std::string result;
    for(int i = 0; i < times; i++)
        result += s;
    return result;
}   


bool is_invalid(long long id){
    std::string id_str = std::to_string(id);
    int len = id_str.length();
    for(int i = 1; i <= len / 2; i++){
        std::string candidate = id_str.substr(0, i);
        std::string repeated = concat(candidate, len / i);
        if(repeated.compare(id_str) == 0)
            return true;
    }
    return false;
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