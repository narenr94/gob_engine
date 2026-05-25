#pragma once

#include <random>
#include <algorithm>
#include <vector>
#include <string>

// Roll a die with 'sides' number of faces (default = 6)
unsigned short int rollDie(int sides = 6) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, sides);

    return dist(gen);
}

std::vector<std::string> chooseRandomOptions(const std::vector<std::string>& t_options, unsigned short t_count) {
    
    if (t_count == 0) {
        return {};
    }

    if (t_count >= t_options.size()) {
        return t_options; 
    }

    std::vector<std::string> pool = t_options;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(pool.begin(), pool.end(), gen);

    return std::vector<std::string>(pool.begin(), pool.begin() + t_count);
}