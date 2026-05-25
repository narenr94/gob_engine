#include "commonJsonParser.h"

#include "raceData.h"

#include "utilities.h"

void extractAndApplyAbilityMods(json& j, RaceData& raceData){
    if(j.contains("ability_mods")){
        for (const auto& mod : j["ability_mods"]) {
            std::string ability = mod["ability"];
            int value = mod["mod"];
            raceData.addAbilityMod(ability, value);
        }
    }
}

void extractAndApplyParamMods(json& j, RaceData& raceData){
    if(j.contains("param_mod")){
        for (const auto& mod : j["param_mod"]) {
            std::string param = mod["param"];
            int value = mod["mod"];
            raceData.addParamMod(param, value);
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