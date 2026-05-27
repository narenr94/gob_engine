#include "raceData.h"
#include "commonJsonParser.h"
#include <filesystem>

void RaceData::applyRaceData(Character* t_character){
    // Stub: Character operations are not tested here
}

void RaceData::printData(){
    // Stub: Logging is not tested here
}

void RaceData::setAgeData(unsigned short int maturityAge, unsigned short int avgLifespan){
    // Stub: Internal state changes not tested
}

void RaceData::setAlignment(Alignment t_alignment){
    // Stub: Internal state changes not tested
}

void RaceData::setSizeData(const SizeCategory category, float height, float weight){
    // Stub: Internal state changes not tested
}

void RaceData::setSpeed(float t_speed){
    // Stub: Internal state changes not tested
}

void RaceData::setDarkvisionData(bool hasDarkvision, std::pair<IlluminationType, float> dim_light_eq, std::pair<IlluminationType, float> darkvision_eq){
    // Stub: Internal state changes not tested
}

void RaceData::setSleepDuration(float duration){
    // Stub: Internal state changes not tested
}

//-----additive data

void RaceData::setProficiencyData(const ProficiencyType t_type, const std::string& proficiency){
    // Stub: Internal state changes not tested
}

void RaceData::addAbilityMod(const std::string& ability, int mod){
    // Stub: Internal state changes not tested
}

void RaceData::addParamMod(const std::string& param, int mod){
    // Stub: Internal state changes not tested
}

void RaceData::addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){
    // Stub: Internal state changes not tested
}

void RaceData::addResilience(const std::string& affliction, bool immune, bool hasAdvantage, bool hasResistance){
    // Stub: Internal state changes not tested
}

void RaceData::updateOptionsData(const OptionsData& t_optionsData){
    // Stub: Internal state changes not tested
}

// Fake implementation: just validates JSON structure without populating RaceData
void getRaceDataFrom(const std::string& t_racePath, RaceData& raceData){
    json j;
    if(readJsonFile(t_racePath, j)){
        // Basic validation that's needed for GameData tests
        if(j.contains("base_race")){
            // Simplified: don't recursively process base races in tests
            // Extract functions are stubs, so no actual data is set
            if(j["base_race"].is_string()){
                std::string baseRaceName = j["base_race"];
                if (!baseRaceName.empty()) {
                    std::string baseRacePath = std::filesystem::path(t_racePath).parent_path().string() + "/" + baseRaceName + ".json";
                    // In tests, we don't recursively load base races to keep it simple
                }
            }
        }
        else{
            throw std::runtime_error("base_race key not found in race JSON file:" + t_racePath);
        }
    }
    // If file doesn't exist or can't be read, RaceData remains in default state
}