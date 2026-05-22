#pragma once

#include "defines.h"
#include "jsonCommonParser.h"

#include <string>
#include <filesystem>

void extractAndApplyAbilityMods(json& j, RaceData& raceData){
    if(j.contains("ability_mods")){
        for (const auto& mod : j["ability_mods"]) {
            std::string ability = mod["ability"];
            int value = mod["mod"];
            raceData.addAbilityMod(ability, value);
        }
    }
}

void extractAndApplyAgeData(json& j, RaceData& raceData){
    if(j.contains("age")){
        unsigned short int maturityAge = j["age"]["mature"];
        unsigned short int avgLifespan = j["age"]["life_span"];
        raceData.setAgeData(maturityAge, avgLifespan);
    }
}

void extractAndApplyAlignmentData(json& j, RaceData& raceData){
    if(j.contains("alignment")){
        Alignment alignment = stringToAlignment(j["alignment"]);
        raceData.setAlignment(alignment);
    }
}

void extractAndApplySizeData(json& j, RaceData& raceData){
    if(j.contains("size")){
        SizeCategory szCat = stringToSizeCategory(j["size"]["category"]);
        raceData.setSizeData(szCat, j["size"]["avg_height_m"], j["size"]["avg_weight_kg"]);
    }
}

void extractAndApplySpeedData(json& j, RaceData& raceData){
    if(j.contains("speed_mps")){
        raceData.setSpeed(j["speed_mps"]);
    }
}

void extractAndApplyLanguagesData(json& j, RaceData& raceData){
    if(j.contains("languages")){
        for (const auto& lang : j["languages"]) {
            std::string language = lang["name"];
            bool speak = lang["speak"];
            bool read = lang["read"];
            bool write = lang["write"];
            raceData.addLanguageProficiency(language, speak, read, write);
        }
    }
}

void extractAndApplyDarkVisionData(json& j, RaceData& raceData){
    if(j.contains("dark_vision")){
        bool hasDarkvision = j["dark_vision"]["has_darkvision"];

        IlluminationType dimLightEq = stringToIlluminationType(j["dark_vision"]["dim_light_eq"]["as_ambient"]); 
        float hasDimLightEqDist = j["dark_vision"]["dim_light_eq"]["distance_m"];
        IlluminationType darkLightEq = stringToIlluminationType(j["dark_vision"]["darkness_eq"]["as_ambient"]);
        float hasDarkvisionEqDist = j["dark_vision"]["darkness_eq"]["distance_m"];

        raceData.setDarkvisionData(hasDarkvision, std::pair<IlluminationType, float>(dimLightEq, hasDimLightEqDist), 
        std::pair<IlluminationType, float>(darkLightEq, hasDarkvisionEqDist));
    }
}

void extractAndApplyResilienceData(json& j, RaceData& raceData){
    if(j.contains("resilience")){
        for(const auto& res : j["resilience"]){

            std::string affliction = res["affliction"];
            bool immune = false;
            if(res.contains("immune")){
                immune = res["immune"];
            }
            bool hasAdvantage = false;
            if(res.contains("has_advantage")){
                hasAdvantage = res["has_advantage"];
            }
            bool hasResistance = false;
            if(res.contains("has_resistance")){
                hasResistance = res["has_resistance"];
            }

            raceData.addResilience(affliction, immune, hasAdvantage, hasResistance);
        }
    }
}

void extractAndApplyProficiencyData(json& j, RaceData& raceData){
    if(j.contains("proficiency")){
        if(j["proficiency"].contains("weapons")){
            for(const auto& wp : j["proficiency"]["weapons"]){
                raceData.setProficiencyData(ProficiencyType::Weapon, wp);
            }
        }

        if(j["proficiency"].contains("armors")){
            for(const auto& ar : j["proficiency"]["armors"]){
                raceData.setProficiencyData(ProficiencyType::Armor, ar);
            }
        }

        if(j["proficiency"].contains("tools")){
            for(const auto& tl : j["proficiency"]["tools"]){
                raceData.setProficiencyData(ProficiencyType::Tool, tl);
            }
        }
    }
}

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
