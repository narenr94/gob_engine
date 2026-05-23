#pragma once
#include "defines.h"
#include "commonJsonParser.h"

#define ABILITY_JSON_PATH "/home/user/gob_engine/game_data/abilities.json"
#define PARAM_JSON_PATH "/home/user/gob_engine/game_data/param.json"

void extractAndApplyAbilities(const std::string& t_abilityPath){
    json j;
    if(readJsonFile(t_abilityPath, j)){
        if(j.contains("abilities") && j["abilities"].is_array()){
            for(const auto& ability : j["abilities"]){
                g_abilitiesVector.push_back(ability);
            }
        }
        else{
            throw std::runtime_error("Key 'abilities' not found or is not an array in abilities JSON file:" + t_abilityPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_abilityPath);
    }
}

void extractAndApplyParams(const std::string& t_paramPath){
    json j;
    if(readJsonFile(t_paramPath, j)){
        if(j.contains("params") && j["params"].is_array()){
            for(const auto& param : j["params"]){
                g_characterParamsVector.push_back(param);
            }
        }
        else{
            throw std::runtime_error("Key 'params' not found or is not an array in params JSON file:" + t_paramPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_paramPath);
    }
}
