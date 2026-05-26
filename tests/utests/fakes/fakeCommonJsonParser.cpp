#include "commonJsonParser.h"
#include <fstream>
#include <filesystem>

// Fake implementation: simplified JSON reading for testing
bool readJsonFile(const std::string& filePath, json& j){
    std::ifstream i(filePath);
    if(!i.is_open()){
        return false;
    }
    try {
        j = json::parse(i);
        return true;
    } catch (...) {
        return false;
    }
}

void printJson(const json& j){
    // No-op in tests
}

void extractAndApplyAbilityMods(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyParamMods(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyAgeData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyAlignmentData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplySizeData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplySpeedData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyLanguagesData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyDarkVisionData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyResilienceData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

void extractAndApplyProficiencyData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

std::vector<std::string> extractAndApplyAbilities(const std::string& t_abilityPath){
    json j;
    std::vector<std::string> abilitiesVector;
    if(readJsonFile(t_abilityPath, j)){
        if(j.contains("abilities") && j["abilities"].is_array()){
            for(const auto& ability : j["abilities"]){
                abilitiesVector.push_back(ability);
            }
        }
        else{
            throw std::runtime_error("Key 'abilities' not found or is not an array in abilities JSON file:" + t_abilityPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_abilityPath);
    }
    return abilitiesVector;
}

std::vector<std::string> extractAndApplyParams(const std::string& t_paramPath){
    json j;
    std::vector<std::string> paramsVector;
    if(readJsonFile(t_paramPath, j)){
        if(j.contains("params") && j["params"].is_array()){
            for(const auto& param : j["params"]){
                paramsVector.push_back(param);
            }
        }
        else{
            throw std::runtime_error("Key 'params' not found or is not an array in params JSON file:" + t_paramPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_paramPath);
    }
    return paramsVector;
}


std::vector<std::string> findAllRaces(const std::string& t_racePath){
    std::vector<std::string> racesVector;

    if (!std::filesystem::exists(t_racePath) || !std::filesystem::is_directory(t_racePath)) {
        return racesVector;
    }

    for (const auto& entry : std::filesystem::directory_iterator(t_racePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            json j;
            if (readJsonFile(entry.path().string(), j)){
                if(j.contains("name")){
                    if(j.contains("is_abstract")){
                        if(j["is_abstract"] == false){
                            racesVector.push_back(j["name"]);
                        }
                    }
                    else{
                        throw std::runtime_error("Key 'is_abstract' not found in race JSON file:" + entry.path().string());
                    }
                }
                else{
                    throw std::runtime_error("Key 'name' not found in race JSON file:" + entry.path().string());
                }
            }
        }
    }
    return racesVector;
}

void extractAndApplySleepDurationData(json& j, RaceData& raceData){
    // Stub: RaceData operations are faked
}

std::vector<std::string> getProficiencyChoices(json& j, const std::string& profType, bool enablePlayerInputs){
    return {};
}

void processProficiencyOptions(json& j, RaceData& raceData, bool enablePlayerInputs){
    // Stub: RaceData operations are faked
}

void processLanguageOptions(json& j, RaceData& raceData, bool enablePlayerInputs){
    // Stub: RaceData operations are faked
}

void extractAndApplyOptionsData(json& j, RaceData& raceData, bool enablePlayerInputs){
    // Stub: RaceData operations are faked
}

std::vector<std::string> extractAllLanguages(const std::string& t_languagesPath){
    json j;
    std::vector<std::string> languagesVector;
    if(readJsonFile(t_languagesPath, j)){
        if(j.contains("languages") && j["languages"].is_array()){
            for(const auto& language : j["languages"]){
                languagesVector.push_back(language);
            }
        }
        else{
            throw std::runtime_error("Key 'languages' not found or is not an array in languages JSON file:" + t_languagesPath);
        }
    }
    else{
        throw std::runtime_error("File not found:" + t_languagesPath);
    }
    return languagesVector;
}