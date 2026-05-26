#pragma once

#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;


bool readJsonFile(const std::string& filePath, json& j);

void printJson(const json& j);

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
void extractAndApplySleepDurationData(json& j, RaceData& raceData);

void extractAndApplyOptionsData(json& j, RaceData& raceData, bool enablePlayerInputs);

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath);
std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath);
std::vector<std::string> extractAllLanguages(const std::string& t_languagesPath);
std::vector<std::string> findAllRaces(const std::string& t_racePath);

