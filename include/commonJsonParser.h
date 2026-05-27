#pragma once
#include "defines.h"
#include "json.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool readJsonFile(const std::string& filePath, json& j);

void printJson(const json& j);

void extractAndApplyAbilityMods(json& j, std::vector<AbilityModData>& abilityModsData);
void extractAndApplyParamMods(json& j, std::vector<ParamModData>& paramModsData);
void extractAndApplyAlignmentData(json& j, Alignment& alignment);
void extractAndApplySizeData(json& j, SizeData& sizeData);
void extractAndApplyAgeData(json& j, AgeData& ageData);
void extractAndApplySpeedData(json& j, float& speedData);
void extractAndApplyLanguagesData(json& j, std::vector<LanguageData>& languageData);
void extractAndApplyDarkVisionData(json& j, DarkvisionData& darkvisionData);
void extractAndApplyResilienceData(json& j, std::vector<ResilienceData>& resilienceData);
void extractAndApplyProficiencyData(json& j, ProficiencyData& proficiencyData);
void extractAndApplySleepDurationData(json& j, float& sleepDurationData);

void extractAndApplyOptionsData(json& j, OptionsData& optionsData);

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath);
std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath);
std::vector<std::string> extractAllLanguages(const std::string& t_languagesPath);
std::vector<std::string> findAllRaces(const std::string& t_racePath);

