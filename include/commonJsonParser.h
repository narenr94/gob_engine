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

struct RaceData; //Forward declaration

void extractAndApplyAbilityMods(json& j, RaceData& raceData);
void extractAndApplyParamMods(json& j, RaceData& raceData);
void extractAndApplyAlignmentData(json& j, RaceData& raceData);
void extractAndApplySizeData(json& j, RaceData& raceData);
void extractAndApplyAgeData(json& j, RaceData& raceData);
void extractAndApplySpeedData(json& j, RaceData& raceData);
void extractAndApplyLanguagesData(json& j, RaceData& raceData);
void extractAndApplyDarkVisionData(json& j, RaceData& raceData);
void extractAndApplyResilienceData(json& j, RaceData& raceData);
void extractAndApplyProficiencyData(json& j, RaceData& raceData);

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath);
std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath);
std::vector<std::string> findAllRaces(const std::string& t_racePath);

