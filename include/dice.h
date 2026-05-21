#pragma once

#include <random>

// Roll a die with 'sides' number of faces (default = 6)
unsigned short int rollDie(int sides = 6) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, sides);

    return dist(gen);
}