#pragma once

#include "defines.h"
#include "commonJsonParser.h"

#include <string>
#include <filesystem>

class Character; //Forward declaration

struct RaceData{

    private:

    std::vector<AbilityModData> abilityModData;
    std::vector<ParamModData> paramModData;
    AgeData ageData;
    Alignment alignment;
    SizeData sizeData;
    float speed;
    std::vector<LanguageData> languagesVector;
    ProficiencyData proficiencyData;
    std::vector<ResilienceData> resilienceDataVector;
    DarkvisionData darkvisionData;

    public:

    //-----replace data

    void setAgeData(unsigned short int maturityAge, unsigned short int avgLifespan){
        ageData.maturityAge = maturityAge;
        ageData.avgLifespan = avgLifespan;
    }

    void setAlignment(Alignment t_alignment){
        alignment = t_alignment;
    }

    void setSizeData(const SizeCategory category, float height, float weight){
        sizeData.category = category;
        sizeData.dimensions = {height, weight};
    }

    void setSpeed(float t_speed){
        speed = t_speed;
    }

    void setDarkvisionData(bool hasDarkvision, std::pair<IlluminationType, float> dim_light_eq, std::pair<IlluminationType, float> darkvision_eq){
        darkvisionData.hasDarkvision = hasDarkvision;
        darkvisionData.dim_light_eq = dim_light_eq.first;
        darkvisionData.dim_light_eq_dist = dim_light_eq.second;
        darkvisionData.darkvision_eq = darkvision_eq.first;
        darkvisionData.darkvision_eq_dist = darkvision_eq.second;
    }


    //-----additive data

    void setProficiencyData(const ProficiencyType t_type, const std::string& proficiency){
    
        switch (t_type)
        {
        case ProficiencyType::Weapon:
            proficiencyData.weaponProficiencies.push_back(proficiency);
            break;
        case ProficiencyType::Armor:
            proficiencyData.armorProficiencies.push_back(proficiency);
            break;
        case ProficiencyType::Tool:
            proficiencyData.toolProficiencies.push_back(proficiency);
            break;
        default:
            break;
        }
    
    }

    

    void addAbilityMod(const std::string& ability, int mod){
        bool modExists = false;

        for(const auto& am : abilityModData){
            if(am.abilityMod.first == ability){
                modExists = true;
                const_cast<std::pair<std::string, int>&>(am.abilityMod).second += mod;
                break;
            }
        }

        if(!modExists){
            AbilityModData newMod;
            newMod.abilityMod = {ability, mod};

            abilityModData.push_back(newMod);
        }

    }

    void addParamMod(const std::string& param, int mod){
        bool modExists = false;

        for(const auto& pm : paramModData){
            if(pm.paramMod.first == param){
                modExists = true;
                const_cast<std::pair<std::string, int>&>(pm.paramMod).second += mod;
                break;
            }
        }

        if(!modExists){
            ParamModData newMod;
            newMod.paramMod = {param, mod};

            paramModData.push_back(newMod);
        }

    }

    void addLanguageProficiency(const std::string& language, bool speak, bool read, bool write){
    
        bool languageExists = false;

        for(const auto& lang : languagesVector){
            if(lang.language == language){
                languageExists = true;

                if(speak){
                    const_cast<LanguageData&>(lang).speak = true;
                }

                if(read){
                    const_cast<LanguageData&>(lang).read = true;
                }
                if(write){
                    const_cast<LanguageData&>(lang).write = true;
                }

                break;
            }
        }

        if(!languageExists){
            LanguageData newLanguage;
            newLanguage.language = language;
            newLanguage.speak = speak;
            newLanguage.read = read;
            newLanguage.write = write;

            languagesVector.push_back(newLanguage);
        }
    
    }

    void addResilience(const std::string& affliction, bool immune, bool hasAdvantage, bool hasResistance){
        
        bool resilienceExists = false;
        for(const auto& res : resilienceDataVector){
            if(res.affliction == affliction){
                resilienceExists = true;
                if(immune){
                    const_cast<ResilienceData&>(res).immune = true;
                }
                if(hasAdvantage){
                    const_cast<ResilienceData&>(res).hasAdvantage = true;
                }
                if(hasResistance){
                    const_cast<ResilienceData&>(res).hasResistance = true;
                }
                break;
            }
        }

        if(!resilienceExists){
            ResilienceData data;
            data.affliction = affliction;
            data.immune = immune;
            data.hasAdvantage = hasAdvantage;
            data.hasResistance = hasResistance;

            resilienceDataVector.push_back(data);
        }
    }

    void printData();
    void applyRaceData(Character* t_character);


};

//------Vector of Races

std::vector<std::pair<std::string, RaceData>> g_racesVector;


//----------------------



void getRaceDataFrom(const std::string& t_racePath, RaceData& raceData){
    
    json j;
    if(readJsonFile(t_racePath, j)){

        if(j.contains("base_race")){

            if(j["base_race"].is_string()){
                std::string baseRaceName = j["base_race"];
                std::string baseRacePath = std::filesystem::path(t_racePath).parent_path().string() + "/" + baseRaceName + ".json";
                getRaceDataFrom(baseRacePath, raceData);
            }
            
            //ability mods
            extractAndApplyAbilityMods(j, raceData);

            //param mods
            extractAndApplyParamMods(j, raceData);

            //age
            extractAndApplyAgeData(j, raceData);

            //alignment
            extractAndApplyAlignmentData(j, raceData);

            //size
            extractAndApplySizeData(j, raceData);

            //speed
            extractAndApplySpeedData(j, raceData);

            //languages
            extractAndApplyLanguagesData(j, raceData);

            //darkvision
            extractAndApplyDarkVisionData(j, raceData);

            //resilience
            extractAndApplyResilienceData(j, raceData);

            //proficiencies
            extractAndApplyProficiencyData(j, raceData);

            //todo : options and traits

        }
        else{
            throw std::runtime_error("base_race key not found in race JSON file:" + t_racePath);
        }

    }
}

void findAllRaces(const std::string& t_racePath){

    if (!std::filesystem::exists(t_racePath) || !std::filesystem::is_directory(t_racePath)) {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(t_racePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            
            json j;
            if (readJsonFile(entry.path().string(), j)){
                if(j.contains("name")){

                    if(j.contains("is_abstract")){

                        if(j["is_abstract"] == false){
                            RaceData raceData;
                            getRaceDataFrom(entry.path().string(), raceData);
                            g_racesVector.push_back({j["name"], raceData});
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

}
