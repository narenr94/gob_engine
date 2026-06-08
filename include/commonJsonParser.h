#pragma once

#include <vector>
#include <string>

struct ConsolidatedData;
struct ConsolidatedOptionsData;

void updateConsolidatedData(const std::string& t_path, ConsolidatedData& conData);

void updateConsolidatedOptionsData(const std::string& t_path, ConsolidatedOptionsData& optionsData);

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath);
std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath);
std::vector<std::string> extractAllLanguages(const std::string& t_languagesPath);

std::string getName(const std::string& t_path);
bool getIfAbstract(const std::string& t_path);
bool getBaseRace(const std::string& t_racePath, std::string& baseRace);
bool getBaseClass(const std::string& t_classPath, std::string& baseClass);
