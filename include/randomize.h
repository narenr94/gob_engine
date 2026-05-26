#pragma once

#include <vector>
#include <string>

// Roll a die with 'sides' number of faces (default = 6)
unsigned short int rollDie(int sides = 6);

std::vector<std::string> chooseRandomOptions(const std::vector<std::string>& t_options, unsigned short t_count);