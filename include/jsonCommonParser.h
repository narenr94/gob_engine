#pragma once

#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;


bool readJsonFile(const std::string& filePath, json& j){
    std::ifstream i(filePath);
    if(!i.is_open()){
        return false;
    }
    j = json::parse(i);
    return true;
}

void printJson(const json& j){
    std::cout << j.dump(4) << std::endl;
}